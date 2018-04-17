#pragma once

#include "IExp.h"

#include <irt/Label.h>

namespace NIRTree {
    class Name : public IExp {
    public:
        const Label *label;

        Name(const Location &location = Location())
            : label(LabelHolder::GetNextLabel()), location(location) {
        }

        Name(const std::string &name)
            : label(LabelHolder::GetLabel(name), location(location)) {
        }

        void Accept(IIRVisitor *visitor) const override {
            visitor->Visit(this);
        }
    };
}