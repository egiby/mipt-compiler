#include "GlobalIRTParent.h"
#include "IIRVisitor.h"

namespace NIRTree {
    void GlobalIRTParent::Accept(NIRTree::IIRVisitor *visitor) const {
        visitor->Visit(this);
    }
}