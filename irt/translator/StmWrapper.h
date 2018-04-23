#pragma once

#include <irt/ISubtreeWrapper.h>

namespace NIRTree {
    class StmWrapper : public ISubtreeWrapper {
        virtual IStm* ToConditional(CJump::EJumpType eJumpType, const Label *trueLabel, const Label *falseLabel) override;
        void Accept(IIRVisitor *visitor) const override;
    };
}