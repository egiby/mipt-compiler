#pragma once

#include "INode.h"

#include <vector>

namespace NIRTree {
    class GlobalIRTParent : public INode {
    public:
        std::vector<const INode*> roots;

        void Accept(NIRTree::IIRVisitor *visitor) const override;
        void Accept(NIRTree::IIRMutableVisitor *visitor) override {}
    };
}