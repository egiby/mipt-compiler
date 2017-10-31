#include "Expression.h"
#include "IVisitor.h"

void NSyntaxTree::BinaryExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayElementAccessExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayLengthExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::MethodCallExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::IntegerLiteralExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::BoolLiteralExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::IdentifierExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::ThisExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::NewIntArrayExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::NewExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::NegateExpression::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}
