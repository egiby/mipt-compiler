#include "VarDeclaration.h"

#include "IVisitor.h"

namespace NSyntaxTree {
    void VarDeclaration::Accept(const IVisitor *visitor) {
        visitor->Visit(this);
    }
}