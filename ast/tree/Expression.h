#pragma once

#include "common.h"

#include "INode.h"

namespace NSyntaxTree {
    enum EBinaryExprType {
        AND,
        LESS,
        PLUS,
        MINUS,
        MULTIPLY
    };

    interface IExpression : public INode {
    };

    struct BinaryExpression : public IExpression {
        EBinaryExprType type;
        unique_ptr<IExpression> left;
        unique_ptr<IExpression> right;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct ArrayElementAccessExpression : public IExpression {
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct ArrayLengthExpression : public IExpression {
        unique_ptr<IExpression> array;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct MethodCallExpression : public IExpression {
        unique_ptr<IExpression> object;
        string nameId;
        vector<unique_ptr<IExpression>> args;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct IntegerLiteralExpression : public IExpression {
        int value;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct BoolLiteralExpression : public IExpression {
        bool value;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct IdentifierExpression : public IExpression {
        string identifier;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct ThisExpression : public IExpression {
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct NewIntArrayExpression : public IExpression {
        unique_ptr<IExpression> size;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct NewExpression : public IExpression {
        string classId;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct NegateExpression : public IExpression {
        unique_ptr<IExpression> expression;
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}