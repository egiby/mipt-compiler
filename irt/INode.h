#pragma once

#include "common.h"

#include <util/Location.h>

namespace NIRTree {
    class IIRVisitor;

    interface INode {
        Location location;

        INode() = default;

        inline explicit INode(const Location& location) : location(location) {
        }

        virtual void Accept(IIRVisitor *visitor) const = 0;

        virtual ~INode() = default;
    };
}