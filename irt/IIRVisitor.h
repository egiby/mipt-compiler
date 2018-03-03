#pragma once

#include <ast/tree/common.h>
#include <ast/tree/NodeTypes.h>

namespace NIRTree {
    interface IIRVisitor {
        virtual void AcceptVisitor(IIRVisitor* visitor) const = 0;
    };
}