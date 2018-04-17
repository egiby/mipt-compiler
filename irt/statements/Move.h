#pragma once

#include "IStm.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Move : public IStm {
    public:
        std::unique_ptr<const IExp> dst;
        std::unique_ptr<const IExp> src;
        NSyntaxTree::Location location;

        Move(const IExp *dst, const IExp *src, const NSyntaxTree::Location &_location)
            : dst(dst), src(src), location(_location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}