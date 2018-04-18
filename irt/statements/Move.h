#pragma once

#include "IStm.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Move : public IStm {
    public:
        std::unique_ptr<const IExp> dst;
        std::unique_ptr<const IExp> src;

        Move(const IExp *dst, const IExp *src, const Location &location)
            : IStm(location), dst(dst), src(src) {
        }

        void Accept(IIRVisitor *visitor) const override;
    };
}