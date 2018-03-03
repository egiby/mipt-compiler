#pragma once

#include "IExp.h"

namespace NIRTree {
    class Const : public IExp {
    public:
        const int value;
        NSyntaxTree::Location location;

        Const(int _value, const NSyntaxTree::Location &_location) 
            : value(_value), location(_location) {
        }

        void Accept(IIRVisitor *visitor) const override;
    };
}