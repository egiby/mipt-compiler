#pragma once

#include "IStm.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Exp : public IStm {
    public:
        std::unique_ptr<const IExp> expr;

        Exp(const IExp *expr, const Location &location)
            : IStm(location), expr(expr) {
        }

        void Accept(IIRVisitor *visitor) const override;
    };
}