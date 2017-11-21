#pragma once

#include "common.h"

#include <sstream>

namespace NSyntaxTree {
    class IVisitor;

    struct Position {
        uint32_t line;
        uint32_t column;

        string ToString() const {
            std::stringstream buf;
            buf << "("  << line << ", " << column << ")";
            return buf.str();
        }
    };

    struct Location {
        Position begin;
        Position end;

        string ToString() const {
            return begin.ToString() + " - " + end.ToString();
        }
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