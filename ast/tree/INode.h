#pragma once

#include "common.h"

namespace NSyntaxTree {
    class IVisitor;

    class INode {
    protected:
        virtual void Accept(const IVisitor *visitor) = 0;
    };
}