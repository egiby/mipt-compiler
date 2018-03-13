#pragma once


#include "IExp.h"

#include <irt/IIRVisitor.h>
#include <irt/statements/IStm.h>

namespace NIRTree {
    class ESeq : public IExp {
    public: 
        std::unique_ptr<const IStm> stm;
        std::unique_ptr<const IExp> exp;

        ESeq(const IStm *_stm, const IExp *_exp, const NSyntaxTree::Location &_location)
            : stm(_stm), exp(_exp), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}