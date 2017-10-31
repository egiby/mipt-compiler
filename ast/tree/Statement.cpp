#include "Statement.h"

#include "IVisitor.h"

void NSyntaxTree::Statements::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::IfStatement::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::WhileStatement::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::PrintlnStatement::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::AssignStatement::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayElementAssignmentStatement::Accept(const NSyntaxTree::IVisitor *visitor) {
    visitor->Visit(this);
}
