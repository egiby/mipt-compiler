#pragma once

#include <irt/IIRMutableVisitor.h>
#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

namespace NIRTree {

    class CanonisationVisitor;

    class Canoniser {
    public:
        static std::unique_ptr<StmWrapper> RemoveEseqsFromSubtree(std::unique_ptr<ISubtreeWrapper> subtreeWrapper);

        static void Reorder(
            std::unique_ptr<IExp>& exp,
            CanonisationVisitor &cv
        );
    private:
        static bool commute(const IStm* stm, const IExp* exp);
        static bool isNop(const IStm* stm);

        static void liftEseq(CanonisationVisitor &cv);
    };

    class CanonisationVisitor : public IIRMutableVisitor {
    public:

        std::unique_ptr<ESeq> highestEseq;

        void Visit(Binop *) override;
        void Visit(Call *) override;
        void Visit(Const *) override;
        void Visit(ESeq *) override;
        void Visit(Mem *) override;
        void Visit(Name *) override;
        void Visit(Temp *) override;
        void Visit(Unop *) override;

        void Visit(CJump *) override;
        void Visit(Exp *) override;
        void Visit(Jump *) override;
        void Visit(Move *) override;
        void Visit(LabelStm*) override;

        void Visit(ExprWrapper *) override;
        void Visit(StmWrapper *) override;

        void Visit(ExpList *) override;
        void Visit(StmList *) override;
    };
}