#include "Expression.h"
#include "visitors/IVisitor.h"

void NSyntaxTree::BinaryExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayElementAccessExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayLengthExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::MethodCallExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::IntegerLiteralExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::BoolLiteralExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::IdentifierExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::ThisExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::NewIntArrayExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::NewExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::NegateExpression::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}
