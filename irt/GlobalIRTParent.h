#pragma once

#include "INode.h"

namespace NIRTree {
    class GlobalIRTParent : public NIRTree::INode {
    public:
        //std::unique_ptr<const IExp> exp;
        void Accept(NIRTree::IIRVisitor *visitor) const override;
    };
}