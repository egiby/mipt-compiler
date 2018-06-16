#pragma once

#include <ast/tree/visitors/IVisitor.h>

#include <irt/common.h>
#include <irt/ISubtreeWrapper.h>
#include <irt/activation_records/IFrame.h>

#include <util/StringInterner.h>
#include <symbol_table/SymbolTable.h>

namespace NIRTree {
    class IRBuilderVisitor: public NSyntaxTree::IVisitor {
    public:
        void Visit(const NSyntaxTree::Program *) override;

        void Visit(const NSyntaxTree::ClassDeclaration *) override;

        void Visit(const NSyntaxTree::MainClass *) override;

        void Visit(const NSyntaxTree::VarDeclaration *) override;

        void Visit(const NSyntaxTree::MethodDeclaration *) override;

        void Visit(const NSyntaxTree::Statements *) override;

        void Visit(const NSyntaxTree::IfStatement *) override;

        void Visit(const NSyntaxTree::WhileStatement *) override;

        void Visit(const NSyntaxTree::PrintlnStatement *) override;

        void Visit(const NSyntaxTree::AssignStatement *) override;

        void Visit(const NSyntaxTree::ArrayElementAssignmentStatement *) override;

        void Visit(const NSyntaxTree::BinaryExpression *) override;

        void Visit(const NSyntaxTree::ArrayElementAccessExpression *) override;

        void Visit(const NSyntaxTree::ArrayLengthExpression *) override;

        void Visit(const NSyntaxTree::MethodCallExpression *) override;

        void Visit(const NSyntaxTree::IntegerLiteralExpression *) override;

        void Visit(const NSyntaxTree::BoolLiteralExpression *) override;

        void Visit(const NSyntaxTree::IdentifierExpression *) override;

        void Visit(const NSyntaxTree::ThisExpression *) override;

        void Visit(const NSyntaxTree::NewIntArrayExpression *) override;

        void Visit(const NSyntaxTree::NewExpression *) override;

        void Visit(const NSyntaxTree::NegateExpression *) override;

    private:
        using SubtreePtr = std::unique_ptr<ISubtreeWrapper>;
        std::unordered_map<const Symbol*, SubtreePtr> forest;
        const NSymbolTable::SymbolTable &symbolTable;
        std::unique_ptr<ISubtreeWrapper> mainSubtree;

        const IFrame* frame;
    };
}