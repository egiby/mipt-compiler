#include "MethodDeclaration.h"

#include "IVisitor.h"

void NSyntaxTree::MethodDeclaration::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}
