#pragma once

#include "IStm.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Exp : public IStm {
    public:
        std::unique_ptr<const IExp> expr;

        Exp(const IExp *expr, const NSyntaxTree::Location &location)
            : expr(expr), location(location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}