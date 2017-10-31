#pragma once

#include "common.h"

#include "NodeTypes.h"

namespace NSyntaxTree {
    interface IVisitor {
        virtual void Visit(const Program *) const = 0;

        virtual void Visit(const ClassDeclaration *) const = 0;
        virtual void Visit(const MainClass *) const = 0;

        virtual void Visit(const VarDeclaration *) const = 0;

        virtual void Visit(const MethodDeclaration *) const = 0;

        virtual void Visit(const Statements *) const = 0;
        virtual void Visit(const IfStatement *) const = 0;
        virtual void Visit(const WhileStatement *) const = 0;
        virtual void Visit(const PrintlnStatement *) const = 0;
        virtual void Visit(const AssignStatement *) const = 0;
        virtual void Visit(const ArrayElementAssignmentStatement *) const = 0;

        virtual void Visit(const BinaryExpression *) const = 0;
        virtual void Visit(const ArrayElementAccessExpression *) const = 0;
        virtual void Visit(const ArrayLengthExpression *) const = 0;
        virtual void Visit(const MethodCallExpression *) const = 0;
        virtual void Visit(const IntegerLiteralExpression *) const = 0;
        virtual void Visit(const BoolLiteralExpression *) const = 0;
        virtual void Visit(const IdentifierExpression *) const = 0;
        virtual void Visit(const ThisExpression *) const = 0;
        virtual void Visit(const NewIntArrayExpression *) const = 0;
        virtual void Visit(const NewExpression *) const = 0;
        virtual void Visit(const NegateExpression *) const = 0;
    };
}