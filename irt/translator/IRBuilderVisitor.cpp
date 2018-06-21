#include "IRBuilderVisitor.h"

#include "ExprWrapper.h"
#include "StmWrapper.h"
#include "NameConventions.h"

#include <irt/NodeTypes.h>
#include <irt/activation_records/ArrayStruct.h>
#include <vector>

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
                new Binop(Binop::MULTIPLY, size,
                          new Const(frame->TypeSize(NSymbolTable::IntType), expr->location), expr->location),
                nullptr, expr->location);

        mainSubtree.reset(new ExprWrapper(
                new Call(new Name(NNameConventions::MallocName, expr->location), args, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT_ARRAY));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NewExpression *expr) {
        const auto &classInfo = symbolTable.GetClassInfo(expr->classId);
        std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
        IExp *allocActions = classStruct->AllocateNew(expr->location);
        mainSubtree.reset(new ExprWrapper(allocActions));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, expr->classId));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::NegateExpression *expr) {
        expr->expression->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Unop(Unop::NOT, mainSubtree->ToExp(), expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::IdentifierExpression *expr) {
        auto varAccess = frame->GetFormalOrLocal(expr->identifier);
        IExp *varExp = nullptr;

        if (varAccess != nullptr) {
            varExp = varAccess->GetExp(new Temp("fp", expr->location), expr->location);
        } else {
            assert(switcher.CurrentClass() != nullptr);
            std::unique_ptr<IClassStruct> scopedClassStruct(
                    classStructBuilder->GetClassStruct(*switcher.CurrentClass(), symbolTable));
            varExp = scopedClassStruct->GetFieldFrom(
                    expr->identifier,
                    frame->GetFormalOrLocal(
                            symbolTable.GetInterner()->GetIntern("this"))->GetExp(
                            new Temp("fp", expr->location), expr->location),
                    expr->location);
        }

        auto info = symbolTable.FindIdentifier(switcher.CurrentClass(), expr->identifier, switcher.CurrentMethod());
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, info->GetId()));
        mainSubtree.reset(new ExprWrapper(varExp));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ThisExpression *expr) {
        mainSubtree.reset(new ExprWrapper(
                new Mem(frame->GetFormalOrLocal(symbolTable.GetInterner()->GetIntern("this"))->GetExp(
                        new Temp("fp", expr->location), expr->location),
                        expr->location)));
        assert(switcher.CurrentClass() != nullptr);
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, switcher.CurrentClass()->GetId()));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ArrayLengthExpression *expr) {
        expr->array->Accept(this);
        IExp *arrayBase = mainSubtree->ToExp();
        mainSubtree.reset(new ExprWrapper(ArrayStruct::GetLength(arrayBase, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ArrayElementAccessExpression *expr) {
        expr->array->Accept(this);
        IExp *arrayBase = mainSubtree->ToExp();
        expr->index->Accept(this);
        IExp *elementNumber = mainSubtree->ToExp();
        mainSubtree.reset(new ExprWrapper(ArrayStruct::GetElement(arrayBase, elementNumber, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::MethodCallExpression *expr) {
        expr->object->Accept(this);
        auto baseAddress = new Temp(0, expr->location);
        IExp *baseExp = new ESeq(new Move(baseAddress, mainSubtree->ToExp(), expr->location),
                                 new Mem(new Temp(*baseAddress), expr->location), expr->location);

        assert(switcher.CurrentExprType() != nullptr);
        NSymbolTable::TypeInfo info = *switcher.CurrentExprType();
        assert(info.GetType() == NSymbolTable::CLASS);

        auto arguments = new ExpList(baseExp, nullptr, expr->location);
        for (const auto &arg: *expr->args) {
            arg->Accept(this);
            arguments = new ExpList(mainSubtree->ToExp(), arguments, expr->location);
        }

        auto classInfo = symbolTable.GetClassInfo(info.GetClassId());
        std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
        IExp *methodAddress = classStruct->GetVirtualMethodAddress(
                expr->nameId, new Temp(*baseAddress), expr->location);
        mainSubtree.reset(new ExprWrapper(new Call(methodAddress, arguments, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::PrintlnStatement *stm) {
        stm->toPrint->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Call(new Name("println", stm->location),
                                                   new ExpList(mainSubtree->ToExp(), nullptr, stm->location),
                                                   stm->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::WhileStatement *stm) {
        stm->condition->Accept(this);

        Label *conditionLabel = LabelHolder::GetNextLabel();
        Label *exitLabel = LabelHolder::GetNextLabel();

        IStm *condition = mainSubtree->ToConditional(CJump::NEQ, exitLabel);
        IStm *conditionPart = new Seq(new LabelStm(conditionLabel, stm->location),
                                      condition, stm->location);
        stm->trueStatement->Accept(this);
        IStm *bodyPart = new Seq(mainSubtree->ToStm(), new Jump(conditionLabel, stm->location),
                                 stm->location);
        mainSubtree.reset(new StmWrapper(new Seq(new Seq(conditionPart, bodyPart, stm->location),
                                                 new LabelStm(exitLabel, stm->location),
                                                 stm->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::Statements *node) {
        std::vector<IStm *> statements;
        for (auto &statement: *node->statements) {
            statement->Accept(this);
            statements.push_back(mainSubtree->ToStm());
        }
        assert(!statements.empty());
        if (statements.size() == 1) {
            mainSubtree.reset(new StmWrapper(statements[0]));
        } else {
            IStm *seq = new Seq(statements[0], statements[1], node->location);
            for (size_t i = 2; i < statements.size(); ++i) {
                seq = new Seq(seq, statements[i], node->location);
            }
            mainSubtree.reset(new StmWrapper(seq));
        }
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::AssignStatement *stm) {
        stm->rvalue->Accept(this);
        auto identifierName = stm->lvalue;
        std::shared_ptr<const IAccess> access = frame->GetFormalOrLocal(identifierName);
        IExp *baseAddresss = nullptr;

        if (access != nullptr) {
            baseAddresss = access->GetExp(new Temp("fp", stm->location), stm->location);
        } else {
            auto classInfo = *switcher.CurrentClass();
            std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
            baseAddresss = classStruct->GetFieldFrom(
                    identifierName,
                    frame->GetFormalOrLocal(
                            symbolTable.GetInterner()->GetIntern("this")
                    )->GetExp(new Temp("fp", stm->location), stm->location),
                    stm->location);
        }
        mainSubtree.reset(new StmWrapper(new Move(baseAddresss, mainSubtree->ToExp(), stm->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::ArrayElementAssignmentStatement *stm) {
        stm->index->Accept(this);
        std::unique_ptr<ISubtreeWrapper> elementNumberExp(mainSubtree.release());
        stm->rvalue->Accept(this);

        auto identifierName = stm->arrayId;
        std::shared_ptr<const IAccess> access = frame->GetFormalOrLocal(identifierName);
        IExp *baseAddresss = nullptr;

        if (access != nullptr) {
            baseAddresss = access->GetExp(new Temp("fp", stm->location), stm->location);
        } else {
            auto classInfo = *switcher.CurrentClass();
            std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
            baseAddresss = classStruct->GetFieldFrom(
                    identifierName,
                    frame->GetFormalOrLocal(
                            symbolTable.GetInterner()->GetIntern("this")
                    )->GetExp(new Temp("fp", stm->location), stm->location), stm->location);
        }
        // TODO: тут должен быть WordType, а не IntType. Но увы
        IExp* address = new Mem(new Binop(Binop::PLUS, baseAddresss,
                                          new Binop(Binop::MULTIPLY,
                                                    new Const(frame->TypeSize(NSymbolTable::IntType),
                                                              stm->location),
                                                    elementNumberExp->ToExp(), stm->location),
                                          stm->location),
                                stm->location);
        mainSubtree.reset(new StmWrapper(new Move(address, mainSubtree->ToExp(), stm->location)));
    }

    void IRBuilderVisitor::Visit(const NSyntaxTree::IfStatement *stm) {
        stm->condition->Accept(this);
        Label* elseBranchLabel = LabelHolder::GetNextLabel();
        Label* exitLabel = LabelHolder::GetNextLabel();

        IStm* condition = mainSubtree->ToConditional(CJump::NEQ, elseBranchLabel);

        stm->trueStatement->Accept(this);
        IStm* ifPart = new Seq(mainSubtree->ToStm(),
                               new Jump(exitLabel, stm->location),
                               stm->location);

        stm->falseStatement->Accept(this);
        IStm* elsePart = new Seq(new Seq(new LabelStm(elseBranchLabel, stm->location),
                                         mainSubtree->ToStm(), stm->location),
                                 new Jump(exitLabel, stm->location),
                                 stm->location);
        mainSubtree.reset(new StmWrapper(new Seq(new Seq(condition, new Seq(ifPart, elsePart, stm->location),
                                                         stm->location), new LabelStm(exitLabel, stm->location),
                                                 stm->location)));
    }

}
