#pragma once

#include "IExp.h"

#include <irt/IIRVisitor.h>

namespace NIRTree {
    class Mem : public IExp {
    public:
        std::unique_ptr<const IExp> exp;

        Mem(const IExp *_exp, const NSyntaxTree::Location &_location)
            : exp(_exp), location(_location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}