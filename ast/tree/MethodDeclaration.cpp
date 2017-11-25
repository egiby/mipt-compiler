#include "MethodDeclaration.h"

#include "visitors/IVisitor.h"

void NSyntaxTree::MethodDeclaration::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}
