#include "Canoniser.h"
#include "IRPrettyPrinter.h"

#include <cassert>
#include <vector>


namespace NIRTree {

    StmWrapper *Canoniser::RemoveEseqsFromSubtree(ISubtreeWrapper *subtreeWrapper) {
        CanonisationVisitor cv;
        subtreeWrapper->Accept(&cv);
        return new StmWrapper(cv.GetStatement());
    }

    bool CanonisationVisitor::commute(const IStm *stm, const IExp *exp) {
        return isNop(stm)
               || dynamic_cast<const Name *>(exp) != nullptr
               || dynamic_cast<const Const *>(exp) != nullptr;
    }

    bool CanonisationVisitor::isNop(const IStm *stm) {
        const auto e = dynamic_cast<const Exp *>(stm);
        return e != nullptr && dynamic_cast<const Const *>(e->expr.get()) != nullptr;
    }

    void CanonisationVisitor::liftEseq() {
        Temp *tmp = new Temp();
        if (highestEseq->stm) {
            highestEseq = std::unique_ptr<ESeq>(
                    new ESeq(
                            new Seq(
                                    highestEseq->stm.release(),
                                    new Move(tmp, highestEseq->exp.release(), {}),
                                    {}
                            ),
                            new Mem(new Temp(*tmp), {}),
                            {}
                    )
            );
        } else {
            highestEseq = std::unique_ptr<ESeq>(
                    new ESeq(
                            new Move(tmp, highestEseq->exp.release(), {}),
                            new Mem(new Temp(*tmp), {}),
                            {}
                    )
            );
        }

    }

    std::vector<std::unique_ptr<IStm>> Canoniser::Linearise(StmWrapper *wrapper) {
        std::vector<std::unique_ptr<IStm>> stms;
        Linear(wrapper->ToStm(), stms);
        return stms;
    }

    void Canoniser::Linear(IStm *node, std::vector<std::unique_ptr<IStm>> &stms) {
        if (auto list = dynamic_cast<StmList *>(node)) {
            if (list->head) {
                Linear(list->head.release(), stms);
            }
            if (list->tail) {
                Linear(list->tail.release(), stms);
            }
        } else {
            stms.emplace_back(node);
        }
    }

    std::vector<std::unique_ptr<IStm>> Canoniser::Canonise(ISubtreeWrapper *subtreeWrapper) {
        return Linearise(RemoveEseqsFromSubtree(std::move(subtreeWrapper)));
    }

    /*Visitor*/

    void CanonisationVisitor::Visit(Binop *node) {
        node->leftExp.release()->Accept(this);
        auto leftStm = std::move(highestEseq->stm);
        node->leftExp = std::move(highestEseq->exp);

        node->rightExp.release()->Accept(this);
        auto rightStm = std::move(highestEseq->stm);
        node->rightExp = std::move(highestEseq->exp);

        if (!CanonisationVisitor::commute(rightStm.get(), node->leftExp.get())) {
            highestEseq->stm = std::move(leftStm);
            highestEseq->exp = std::move(node->leftExp);
            liftEseq();
            leftStm = std::move(highestEseq->stm);
            node->leftExp = std::move(highestEseq->exp);
        }

        if (leftStm && rightStm) {
            highestEseq->stm = std::unique_ptr<Seq>(new Seq(leftStm.release(), rightStm.release(), {}));
        } else if (leftStm) {
            highestEseq->stm = std::move(leftStm);
        } else if (rightStm) {
            highestEseq->stm = std::move(rightStm);
        }
        highestEseq->exp = std::unique_ptr<Binop>(node);
    }

    void CanonisationVisitor::Visit(Call *node) {
        node->args.release()->Accept(this);

        IExp *highestEseqExp = highestEseq->exp.release();
        ExpList *expList = dynamic_cast<ExpList *>(highestEseqExp);
        assert(highestEseqExp == nullptr || expList != nullptr);

        node->args.reset(expList);
        node->funcExp.release()->Accept(this);
        node->funcExp = std::move(highestEseq->exp);

        highestEseq->exp.reset(node);

        liftEseq();
    }

    void CanonisationVisitor::Visit(Const *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(ESeq *node) {
        std::unique_ptr<ESeq> nodeHolder(node);
        node->stm.release()->Accept(this);

        node->exp.release()->Accept(this);
    }

    void CanonisationVisitor::Visit(Mem *node) {
        node->exp.release()->Accept(this);
        node->exp = std::move(highestEseq->exp);
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Name *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Temp *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Unop *node) {
        node->expression.release()->Accept(this);
        node->expression = std::move(highestEseq->exp);
        highestEseq->exp = std::unique_ptr<Unop>(node);
    }

    void CanonisationVisitor::Visit(CJump *node) {
        node->leftExpr.release()->Accept(this);
        auto leftStm = std::move(highestEseq->stm);
        node->leftExpr = std::move(highestEseq->exp);

        node->rightExpr.release()->Accept(this);
        auto rightStm = std::move(highestEseq->stm);
        node->rightExpr = std::move(highestEseq->exp);

        if (!CanonisationVisitor::commute(rightStm.get(), node->leftExpr.get())) {
            highestEseq->stm = std::move(leftStm);
            highestEseq->exp = std::move(node->leftExpr);
            liftEseq();
            leftStm = std::move(highestEseq->stm);
            node->leftExpr = std::move(highestEseq->exp);
        }

        highestEseq->AppendStm(std::move(leftStm));
        highestEseq->AppendStm(std::move(rightStm));
        highestEseq->AppendStm(std::unique_ptr<CJump>(node));
    }

    void CanonisationVisitor::Visit(Exp *node) {
        node->expr.release()->Accept(this);
        auto stm = std::move(highestEseq->stm);
        node->expr = std::move(highestEseq->exp);

        highestEseq->AppendStm(std::move(stm));
        highestEseq->AppendStm(std::unique_ptr<Exp>(node));
    }

    void CanonisationVisitor::Visit(Jump *node) {
        highestEseq->AppendStm(std::unique_ptr<Jump>(node));
    }

    void CanonisationVisitor::Visit(Move *node) {
        node->src.release()->Accept(this);
        auto src = std::move(highestEseq->stm);
        node->src = std::move(highestEseq->exp);

        node->dst.release()->Accept(this);
        auto dst = std::move(highestEseq->stm);
        node->dst = std::move(highestEseq->exp);

        if (!CanonisationVisitor::commute(dst.get(), node->src.get())) {
            highestEseq->stm = std::move(src);
            highestEseq->exp = std::move(node->src);
            liftEseq();
            src = std::move(highestEseq->stm);
            node->src = std::move(highestEseq->exp);
        }

        /*std::cerr << "Before appends in MOVE " << node << std::endl;
        NIRTree::IRPrettyPrinter irPrinter(std::cerr);
        node->Accept(&irPrinter);*/

        highestEseq->AppendStm(std::move(src));
        highestEseq->AppendStm(std::move(dst));
        highestEseq->AppendStm(std::unique_ptr<Move>(node));
    }

    void CanonisationVisitor::Visit(LabelStm *node) {
        highestEseq->AppendStm(std::unique_ptr<LabelStm>(node));
    }

    void CanonisationVisitor::Visit(ExprWrapper *node) {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(StmWrapper *node) {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(ExpList *node) {
        if (node->head) {
            assert(!dynamic_cast<ExpList *>(node->head.get()));
            auto highestEseqStm = std::move(highestEseq->stm);
            node->head.release()->Accept(this);
            node->head = std::move(highestEseq->exp);
            auto stm = std::move(highestEseq->stm);

            highestEseq->stm = std::move(highestEseqStm);
            highestEseq->AppendStm(std::move(stm));
        }
        if (node->tail) {
            if (dynamic_cast<ExpList *>(node->tail.get())) {
                node->tail.release()->Accept(this);
                node->tail = std::move(highestEseq->exp);
            } else {
                auto highestEseqStm = std::move(highestEseq->stm);
                node->tail.release()->Accept(this);
                node->tail = std::move(highestEseq->exp);
                auto stm = std::move(highestEseq->stm);

                highestEseq->stm = std::move(highestEseqStm);
                highestEseq->AppendStm(std::move(stm));
            }
        }
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(StmList *node) {
        // std::cerr << "Before " << node << std::endl;
        // NIRTree::IRPrettyPrinter irPrinter(std::cerr);
        // node->Accept(&irPrinter);

        if (node->head) {
            node->head.release()->Accept(this);
            node->head = std::move(highestEseq->stm);
            assert(!highestEseq->exp);
        }

        // std::cerr << "After HEAD " << node << std::endl;
        // node->Accept(&irPrinter);

        if (node->tail) {
            node->tail.release()->Accept(this);
            node->tail = std::move(highestEseq->stm);
            assert(!highestEseq->exp);
        }

        highestEseq->stm = std::unique_ptr<StmList>(node);

        // std::cerr << "After " << node << std::endl;
        // node->Accept(&irPrinter);
    }
}