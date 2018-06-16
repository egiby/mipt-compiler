#include "IRBuilderVisitor.h"

#include "ExprWrapper.h"
#include "StmWrapper.h"
#include "NameConventions.h"

#include <irt/NodeTypes.h>

namespace NIRTree {

    void IRBuilderVisitor::Visit(const NSyntaxTree::Program *program) {
        program->mainClass->Accept(this);

        for (const auto &clazz: *program->classes) {
            clazz->Accept(this);
        }
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::MainClass *clazz) {
        clazz->mainStatement->Accept(this);
        assert(mainSubtree != nullptr);

        const auto id = symbolTable.GetInterner()->GetIntern(clazz->nameId->String() + "@MAIN");
        auto subtree = SubtreePtr(mainSubtree.release());
        forest.insert({id, std::move(subtree)});
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ClassDeclaration *clazz) {
        for (const auto &method: *clazz->methodDeclarations) {
            method->Accept(this);
            assert(mainSubtree != nullptr);

            const auto id = symbolTable.GetInterner()->GetIntern(clazz->id->String()
                    + "@" + method->id->String());
            auto subtree = SubtreePtr(mainSubtree.release());
            forest.insert({id, std::move(subtree)});
        }
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::IntegerLiteralExpression *expr) {
        mainSubtree.reset(new ExprWrapper(new Const(expr->value, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::BoolLiteralExpression *expr) {
        // TODO: Here we loose information about type. Maybe, it is bad
        mainSubtree.reset(new ExprWrapper(new Const(expr->value, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NewIntArrayExpression *expr) {
        expr->size->Accept(this);
        assert(mainSubtree != nullptr);
        auto size = mainSubtree->ToExp();

        auto args = new ExpList(
                new Binop(MULTIPLY, size,
                          new Const(frame->TypeSize(NSymbolTable::IntType), expr->location), expr->location),
                nullptr, expr->location);
        mainSubtree.reset(new ExprWrapper(
                new Call(new Name(NNameConventions::MallocName, expr->location), args, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NewExpression *expr) {
        const auto& classInfo = symbolTable.GetClassInfo(expr->classId);
        // some problems here
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NegateExpression *expr) {
        expr->expression->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Unop(Unop::NOT, mainSubtree->ToExp(), expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ThisExpression *expr) {

    }
}