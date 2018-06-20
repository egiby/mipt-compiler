#pragma once

#include "IExp.h"

namespace NIRTree {
    class Binop : public IExp {
    public:
        enum EBinopType {
            AND = 0,
            OR = 1,
            PLUS = 2,
            MINUS = 3,
            MULTIPLY = 4
        };

        const EBinopType binop;
        std::unique_ptr<const IExp> leftExp;
        std::unique_ptr<const IExp> rightExp;

        Binop(EBinopType _binop,
              const IExp *_leftExp, 
              const IExp *_rightExp, 
              const Location &_location)
            : IExp(_location), binop(_binop), leftExp(_leftExp), rightExp(_rightExp) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };
}