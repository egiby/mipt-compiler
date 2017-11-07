#include "Statement.h"

#include "visitors/IVisitor.h"

void NSyntaxTree::Statements::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::IfStatement::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::WhileStatement::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::PrintlnStatement::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::AssignStatement::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NSyntaxTree::ArrayElementAssignmentStatement::Accept(NSyntaxTree::IVisitor *visitor) const {
    visitor->Visit(this);
}
