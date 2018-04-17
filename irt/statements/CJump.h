#pragma once

#include "IStm.h"
#include "Label.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class CJump : public IStm {
        enum EJumpType {
            EQ,
            NEQ,
            LT
        };

        CJump(const EJumpType jumpType,
              const IExp *leftExpr,
              const IExp *rightExpr,
              const Label *trueLabel,
              const Label *falseLabel,
              const Location &location)
            : leftExp(leftExpr), rightExpr(rightExpr),
              trueLabel(trueLabel), falseLabel(falseLabel),
              jumpType(jumpType),
              location(location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }

        std::unique_ptr<const IExp> leftExpr;
        std::unique_ptr<const IExp> rightExpr;

        const Label *trueLabel;
        const Label *falseLabel;

        const EJumpType jumpType;
    };
}