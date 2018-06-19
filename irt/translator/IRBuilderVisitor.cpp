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
        switcher.SwitchClass(new NSymbolTable::ClassInfo(symbolTable.GetClassInfo(clazz->id)));
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
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
        mainSubtree.reset(new ExprWrapper(new Const(expr->value, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::BoolLiteralExpression *expr) {
        // TODO: Here we loose information about type. Maybe, it is bad
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
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
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT_ARRAY));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NewExpression *expr) {
        const auto& classInfo = symbolTable.GetClassInfo(expr->classId);
        std::unique_ptr<IClassStruct> classStruct = classStructBuilder->GetClassStruct(classInfo, symbolTable);
        IExp* allocActions = classStruct->AllocateNew(expr->location);
        mainSubtree.reset(new ExprWrapper(allocActions));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, expr->classId));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NegateExpression *expr) {
        expr->expression->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Unop(Unop::NOT, mainSubtree->ToExp(), expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
    }
}