#pragma once

#include "IExp.h"

#include <irt/IIRVisitor.h>

namespace NIRTree {
    enum EBinopType {
        AND,
        OR,
        PLUS,
        MINUS,
        MULTIPLY
    };

    class Binop : public IExp {
    public:
        const EBinopType binop;
        std::unique_ptr<const IExp> leftExp;
        std::unique_ptr<const IExp> rightExp;

        Binop(EBinopType _binop,
              const IExp *_leftExp, 
              const IExp *_rightExp, 
              const NSyntaxTree::Location &_location) 
            : binop(_binop), leftExp(_leftExp), rightExp(_rightExp), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}