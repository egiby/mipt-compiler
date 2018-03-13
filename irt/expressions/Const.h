#pragma once

#include "IExp.h"

#include <irt/IIRVisitor.h>

namespace NIRTree {
    class Const : public IExp {
    public:
        const int value;

        Const(int _value, const NSyntaxTree::Location &_location) 
            : value(_value), location(_location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}