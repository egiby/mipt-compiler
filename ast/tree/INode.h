#pragma once

#include "common.h"

namespace NSyntaxTree {
    class IVisitor;

    struct Position {
        uint32_t line;
        uint32_t column;
    };

    struct Location {
        Position begin;
        Position end;
    };

    interface INode {
        Location location;

        INode() = default;

        inline explicit INode(const Location& location) : location(location) {
        }

        virtual void Accept(IVisitor *visitor) const = 0;
        virtual ~INode() {
        }
    };
}