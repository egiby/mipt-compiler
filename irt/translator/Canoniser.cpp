#include "Canoniser.h"

#include <cassert>

//#include <memory>

namespace NIRTree {

    /*public section*/
    std::unique_ptr<StmWrapper> Canoniser::RemoveEseqsFromSubtree(std::unique_ptr<ISubtreeWrapper> subtreeWrapper) {
        CanonisationVisitor cv;
        cv.highestEseq = std::unique_ptr<ESeq>(new ESeq(nullptr, nullptr, {}));
        subtreeWrapper.release()->Accept(&cv);
        return std::unique_ptr<StmWrapper>(new StmWrapper(cv.highestEseq->stm.release()));
    }

    void Canoniser::Reorder(
        std::unique_ptr<IExp>& exp,
        CanonisationVisitor &cv
    ) {
        exp.release()->Accept(&cv);
        liftEseq(cv); 
    }

    /*private section*/

    bool Canoniser::commute(const IStm* stm, const IExp* exp) {
        return isNop(stm) 
            || dynamic_cast<const Name*>(exp) != nullptr 
            || dynamic_cast<const Const*>(exp) != nullptr;
    }

    bool Canoniser::isNop(const IStm* stm) {
        const Exp *e = dynamic_cast<const Exp*>(stm);
        return e != nullptr && dynamic_cast<const Const*>(e->expr.get()) != nullptr;
    }

    void Canoniser::liftEseq(CanonisationVisitor &cv) {
        if(!cv.highestEseq->stm 
            || !cv.highestEseq->exp 
            || commute(cv.highestEseq->stm.get(), cv.highestEseq->exp.get())) {
            return;
        }
        Temp* tmp = new Temp();
        cv.highestEseq = std::unique_ptr<ESeq>(
            new ESeq(
                new Seq(
                    cv.highestEseq->stm.release(),
                    new Move(tmp, cv.highestEseq->exp.release(), {}),
                    {}
                ),
                new Mem(new Temp(*tmp), {}),
                {}
            )
        );
        
    }

    /*Visitor*/

    void CanonisationVisitor::Visit(Binop* node) {
        Canoniser::Reorder(node->leftExp, *this);
        auto leftStm = std::move(highestEseq->stm);
        node->leftExp = std::move(highestEseq->exp);

        Canoniser::Reorder(node->rightExp, *this);
        auto rightStm = std::move(highestEseq->stm);
        node->rightExp = std::move(highestEseq->exp);

        highestEseq->stm = std::unique_ptr<Seq>(new Seq(leftStm.release(), rightStm.release(), {}));
        highestEseq->exp = std::unique_ptr<Binop>(node);
    }   

    void CanonisationVisitor::Visit(Call *node)  {
        node->args.release()->Accept(this);

        IExp *highestEseqExp = highestEseq->exp.release();
        ExpList* expList = dynamic_cast<ExpList*>(highestEseqExp);
        assert(highestEseqExp == nullptr || expList != nullptr);

        node->args.reset(expList);
        Canoniser::Reorder(node->funcExp, *this);
        node->funcExp = std::move(highestEseq->exp);
    }

    void CanonisationVisitor::Visit(Const *node)  {
        highestEseq->exp.reset(node);
    }
    void CanonisationVisitor::Visit(ESeq *node)  {
        std::unique_ptr<ESeq> nodeHolder(node);
        node->stm.release()->Accept(this);

        Canoniser::Reorder(node->exp, *this);
    }
    void CanonisationVisitor::Visit(Mem *node)  {
        node->exp.release()->Accept(this);
        node->exp = std::move(highestEseq->exp);
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Name *node)  {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Temp *node)  {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Unop *node)  {
        Canoniser::Reorder(node->expression, *this);
        node->expression = std::move(highestEseq->exp);
        highestEseq->exp = std::unique_ptr<Unop>(node);
    }

    void CanonisationVisitor::Visit(CJump *node)  {
        Canoniser::Reorder(node->leftExpr, *this);
        auto leftStm = std::move(highestEseq->stm);
        node->leftExpr = std::move(highestEseq->exp);

        Canoniser::Reorder(node->rightExpr, *this);
        auto rightStm = std::move(highestEseq->stm);
        node->rightExpr = std::move(highestEseq->exp);

        highestEseq->AppendStm(std::move(leftStm));
        highestEseq->AppendStm(std::move(rightStm));
        highestEseq->AppendStm(std::unique_ptr<CJump>(node));
    }

    void CanonisationVisitor::Visit(Exp *node)  {
        Canoniser::Reorder(node->expr, *this);
        auto stm = std::move(highestEseq->stm);
        node->expr = std::move(highestEseq->exp);

        highestEseq->AppendStm(std::move(stm));
        highestEseq->AppendStm(std::unique_ptr<Exp>(node));
    }

    void CanonisationVisitor::Visit(Jump *node)  {
        highestEseq->AppendStm(std::unique_ptr<Jump>(node));
    }

    void CanonisationVisitor::Visit(Move *node)  {
        Canoniser::Reorder(node->src, *this);
        auto src = std::move(highestEseq->stm);
        node->src = std::move(highestEseq->exp);

        Canoniser::Reorder(node->dst, *this);
        auto dst = std::move(highestEseq->stm);
        node->dst = std::move(highestEseq->exp);

        highestEseq->AppendStm(std::move(src));
        highestEseq->AppendStm(std::move(dst));
        highestEseq->AppendStm(std::unique_ptr<Move>(node));
    }

    void CanonisationVisitor::Visit(LabelStm *node)  {
        highestEseq->AppendStm(std::unique_ptr<LabelStm>(node));
    }

    void CanonisationVisitor::Visit(ExprWrapper *node)  {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(StmWrapper *node)  {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(ExpList *node)  {
        if(node->head) {
            Canoniser::Reorder(node->head, *this);
            node->head = std::move(highestEseq->exp);
            auto stm = std::move(highestEseq->stm);

            highestEseq->AppendStm(std::move(stm));
        }
        if(node->tail) {
            node->tail.release()->Accept(this);
            node->tail = std::move(highestEseq->exp);
        }
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(StmList *node)  {
        std::unique_ptr<StmList> nodeHandle(node);

        node->head.release()->Accept(this);

        if(node->tail) {
            node->tail.release()->Accept(this);
        }
    }
}