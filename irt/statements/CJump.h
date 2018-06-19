#pragma once

#include "IStm.h"
#include "Label.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class CJump : public IStm {
    public:
        enum EJumpType {
            EQ = 0,
            NEQ = 1,
            LT = 2
        };

        CJump(const EJumpType jumpType,
              const IExp *leftExpr,
              const IExp *rightExpr,
              const Label *trueLabel,
              const Label *falseLabel,
              const Location &location)
            : IStm(location), leftExpr(leftExpr), rightExpr(rightExpr),
              trueLabel(trueLabel), falseLabel(falseLabel),
              jumpType(jumpType) {
        }

        void Accept(IIRVisitor *visitor) const override;

        std::unique_ptr<const IExp> leftExpr;
        std::unique_ptr<const IExp> rightExpr;

        const Label *trueLabel;
        const Label *falseLabel;

        const EJumpType jumpType;
    };
}