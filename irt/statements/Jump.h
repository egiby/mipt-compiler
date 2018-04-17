#pragma once

#include "IStm.h"

#include <irt/Label.h>

namespace NIRTree {
    class Jump : public IStm {
    public:
        const Label *toJump;

        Jump(const Label *label, const Location &location) : location(location), toJump(toJump) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}