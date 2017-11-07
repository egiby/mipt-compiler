#pragma once

#include "ast/tree/common.h"

#include "ast/tree/NodeTypes.h"

namespace NSyntaxTree {
    interface IVisitor {
        virtual void Visit(const Program *) = 0;

        virtual void Visit(const ClassDeclaration *) = 0;
        virtual void Visit(const MainClass *) = 0;

        virtual void Visit(const VarDeclaration *) = 0;

        virtual void Visit(const MethodDeclaration *) = 0;

        virtual void Visit(const Statements *) = 0;
        virtual void Visit(const IfStatement *) = 0;
        virtual void Visit(const WhileStatement *) = 0;
        virtual void Visit(const PrintlnStatement *) = 0;
        virtual void Visit(const AssignStatement *) = 0;
        virtual void Visit(const ArrayElementAssignmentStatement *) = 0;

        virtual void Visit(const BinaryExpression *) = 0;
        virtual void Visit(const ArrayElementAccessExpression *) = 0;
        virtual void Visit(const ArrayLengthExpression *) = 0;
        virtual void Visit(const MethodCallExpression *) = 0;
        virtual void Visit(const IntegerLiteralExpression *) = 0;
        virtual void Visit(const BoolLiteralExpression *) = 0;
        virtual void Visit(const IdentifierExpression *) = 0;
        virtual void Visit(const ThisExpression *) = 0;
        virtual void Visit(const NewIntArrayExpression *) = 0;
        virtual void Visit(const NewExpression *) = 0;
        virtual void Visit(const NegateExpression *) = 0;
    };
}