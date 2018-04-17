#pragma once

#include "IStm.h"

#include <irt/Label.h>

namespace NIRTree {
    class LabelStm : public IStm {
    public:
        const Label *label;

        LabelStm(const Label *label, const Location &location) : label(label), location(location) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}