#pragma once

#include "common.h"

namespace NSyntaxTree {
    class IVisitor;

    interface INode {
        Location location;

        INode() = default;

        inline explicit INode(const Location& location) : location(location) {
        }

        virtual void Accept(IVisitor *visitor) const = 0;
        virtual ~INode() = default;
    };
}