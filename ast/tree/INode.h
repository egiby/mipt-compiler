#pragma once

#include "common.h"

namespace NSyntaxTree {
    class IVisitor;

    interface INode {
        virtual void Accept(IVisitor *visitor) const = 0;
        
        virtual ~INode() {
        }
    };
}