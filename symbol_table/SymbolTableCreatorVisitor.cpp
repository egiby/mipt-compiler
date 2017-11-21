#include "SymbolTableCreatorVisitor.h"

namespace NSymbolTable {
    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::Program *program) {
        InsertAll(&symbolTable, &SymbolTable::InsertClassInfo, &SymbolTable::GetClasses, *program->classes);

        program->mainClass->Accept(this);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ClassDeclaration *classDeclaration) {
        const Symbol *id = interner->GetIntern(classDeclaration->id);
        const Symbol *extends = interner->GetIntern(classDeclaration->extendsId);
        auto classInfo = new ClassInfo(id, classDeclaration->location, extends);

        InsertAll(classInfo, &ClassInfo::InsertVarInfo, &ClassInfo::GetVarsInfo, *classDeclaration->varDeclarations);
        InsertAll(classInfo, &ClassInfo::InsertMethodInfo, &ClassInfo::GetMethodsInfo, *classDeclaration->methodDeclarations);

        returnValue.reset(classInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MainClass *mainClass) {
        symbolTable.SetMainClass(interner->GetIntern(mainClass->nameId));
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::VarDeclaration *var) {
        const Symbol *id = interner->GetIntern(var->id);
        auto varInfo = new VariableInfo(id, var->location, FromType(var->type));

        returnValue.reset(varInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MethodDeclaration *method) {
        const Symbol *id = interner->GetIntern(method->id);
        auto methodInfo = new MethodInfo(id, method->location, FromType(method->returnType), method->modifier);

        InsertAll(methodInfo, &MethodInfo::InsertArgumentInfo, &MethodInfo::GetArgsInfo, *method->args);
        InsertAll(methodInfo, &MethodInfo::InsertVariableInfo, &MethodInfo::GetVarsInfo, *method->localVars);

        returnValue.reset(methodInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::Statements *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IfStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::WhileStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::PrintlnStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::AssignStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayElementAssignmentStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::BinaryExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayElementAccessExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayLengthExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MethodCallExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IntegerLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::BoolLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IdentifierExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ThisExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NewIntArrayExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NewExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NegateExpression *) {
    }
}