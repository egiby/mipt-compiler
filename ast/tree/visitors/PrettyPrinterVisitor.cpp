#include "PrettyPrinterVisitor.h"

namespace NSyntaxTree {

    void PrettyPrinterVisitor::Visit(const Program *node) {
        PrintIndent();
        out << "Program:\n";

        level++;
        node->mainClass->Accept(this);

        for (const auto& classDeclaration: node->classes) {
            classDeclaration->Accept(this);
        }
        level--;
    }

    void PrettyPrinterVisitor::Visit(const ClassDeclaration *node) {
        PrintIndent();
        out << "Class " << node->nameId;
        if (!node->extendsId.empty())
            out << " extends " << node->extendsId;
        out << ":\n";

        level++;
        for (const auto& varDeclaration: node->varDeclarations) {
            varDeclaration->Accept(this);
        }

        for (const auto& methodDeclaration: node->methodDeclarations) {
            methodDeclaration->Accept(this);
        }
        level--;
    }

    void PrettyPrinterVisitor::Visit(const MainClass *node) {
        PrintIndent();
        out << "MAIN:\n";

        level++;
        level--;
    }

    void PrettyPrinterVisitor::Visit(const VarDeclaration *node) {

    }

    void PrettyPrinterVisitor::Visit(const MethodDeclaration *node) {

    }

    void PrettyPrinterVisitor::Visit(const Statements *node) {

    }

    void PrettyPrinterVisitor::Visit(const IfStatement *node) {

    }

    void PrettyPrinterVisitor::Visit(const WhileStatement *node) {

    }

    void PrettyPrinterVisitor::Visit(const PrintlnStatement *node) {

    }

    void PrettyPrinterVisitor::Visit(const AssignStatement *node) {

    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAssignmentStatement *node) {

    }

    void PrettyPrinterVisitor::Visit(const BinaryExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAccessExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const ArrayLengthExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const MethodCallExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const IntegerLiteralExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const BoolLiteralExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const IdentifierExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const ThisExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const NewIntArrayExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const NewExpression *node) {

    }

    void PrettyPrinterVisitor::Visit(const NegateExpression *node) {

    }

    void PrettyPrinterVisitor::PrintIndent() {
        for (int i = 0; i < level; ++i)
            out << "    ";
    }
}