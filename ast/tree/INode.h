#pragma once

#include "common.h"

namespace NSyntaxTree {
    class IVisitor;

    class INode {
    protected:
        virtual void Accept(IVisitor *visitor) const = 0;
    public:
        virtual ~INode() {
        }
    };
}