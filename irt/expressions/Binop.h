#pragma once

#include "IExp.h"

namespace NIRTree {
    enum EBinopType {
        PLUS,
        MINUS,
        MUL,
        DIV,
        AND,
        OR,
        LSHIFT,
        RSHIFT,
        ARHIFT,
        XOR
    };

    class Binop : public IExp {
    public:
        const EBinopType binop;
        NSyntaxTree::Location location;
        std::unique_ptr<const IExp> leftExp;
        std::unique_ptr<const IExp> rightExp;

        Binop(EBinopType _binop,
              const IExp *_leftExp, 
              const IExp *_rightExp, 
              const NSyntaxTree::Location &_location) 
            : binop(_binop), leftExp(_leftExp), rightExp(_rightExp), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };
}