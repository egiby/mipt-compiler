#pragma once

#include "IStm.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Exp : public IStm {
    public:
        std::unique_ptr<const IExp> exp;
        NSyntaxTree::Location location;

        Exp(const IExp *_exp, const NSyntaxTree::Location &_location) 
            : exp(_exp), location(_location) {      
        }
            
        void Accept(IIRVisitor *visitor) const override;      
    };
}