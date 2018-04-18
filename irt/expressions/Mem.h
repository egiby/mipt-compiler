#pragma once

#include "IExp.h"

namespace NIRTree {
    class Mem : public IExp {
    public:
        std::unique_ptr<const IExp> exp;

        Mem(const IExp *_exp, const Location &_location)
            : IExp(_location), exp(_exp) {
        }

        void Accept(IIRVisitor *visitor) const override;
    };
}