#include "SymbolTableVisitor.h"

namespace NSymbolTable {
    void SymbolTableVisitor::Visit(const NSyntaxTree::Program* program) {

    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::ClassDeclaration* classDeclaration) {

    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::MainClass* mainClass) {
        symbolTable.SetMainClass(interner->GetIntern(mainClass->nameId));
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::VarDeclaration* ) {

    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::MethodDeclaration *) {

    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::Statements *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::IfStatement *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::WhileStatement *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::PrintlnStatement *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::AssignStatement *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::ArrayElementAssignmentStatement *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::BinaryExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::ArrayElementAccessExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::ArrayLengthExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::MethodCallExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::IntegerLiteralExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::BoolLiteralExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::IdentifierExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::ThisExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::NewIntArrayExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::NewExpression *) {
    }

    void SymbolTableVisitor::Visit(const NSyntaxTree::NegateExpression *) {
    }
}