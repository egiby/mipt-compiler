#pragma once

#include "IIRVisitor.h"

namespace NIRTree {
    interface INode {
        virtual void Accept(IIRVisitor *visitor) const = 0;
        virtual ~INode() {
        }
    };
}