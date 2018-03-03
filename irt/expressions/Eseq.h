#pragma once

#include "IExp.h"
#include <irt/statements/IStm.h>

namespace NIRTree {
    class Eseq : public IExp {
    public: 
        std::unique_ptr<const IStm> stm;
        std::unique_ptr<const IExp> exp;
        NSyntaxTree::Location location;

        Eseq(const IStm *_stm, const IExp *_exp, const NSyntaxTree::Location &_location)
            : stm(_stm), exp(_exp), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };
}