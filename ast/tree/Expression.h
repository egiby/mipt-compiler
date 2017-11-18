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
        inline explicit IExpression(const Location& location) : INode(location) {
        }
        IExpression() = default;
    };

    struct BinaryExpression : public IExpression {
        EBinaryExprType type;
        unique_ptr<IExpression> left;
        unique_ptr<IExpression> right;

        inline BinaryExpression(const Location& location
            , EBinaryExprType expType
            , IExpression* leftExp
            , IExpression* rightExp)
            : IExpression(location), type(expType), left(leftExp), right(rightExp) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAccessExpression : public IExpression {
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;

        ArrayElementAccessExpression(const Location& location, IExpression* arrayExpr, IExpression* indexExpr)
            : IExpression(location), array(arrayExpr), index(indexExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayLengthExpression : public IExpression {
        unique_ptr<IExpression> array;
        
        inline explicit ArrayLengthExpression(const Location& location, IExpression* expression)
            : IExpression(location), array(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct MethodCallExpression : public IExpression {
        unique_ptr<IExpression> object;
        string nameId;
        unique_ptr<vector<unique_ptr<IExpression>>> args;

        inline MethodCallExpression(const Location& location
            , IExpression* objectExpr
            , const string& name
            , vector<unique_ptr<IExpression>>* argsVector)
            : IExpression(location), object(objectExpr), nameId(name), args(argsVector) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IntegerLiteralExpression : public IExpression {
        int value;

        inline IntegerLiteralExpression(const Location& location, int value)
            : IExpression(location), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct BoolLiteralExpression : public IExpression {
        bool value;

        inline BoolLiteralExpression(const Location& location, bool value)
            : IExpression(location), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IdentifierExpression : public IExpression {
        string identifier;

        inline IdentifierExpression(const Location& location, const string& identifier)
            : IExpression(location), identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ThisExpression : public IExpression {
        inline explicit ThisExpression(const Location& location) : IExpression(location) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NewIntArrayExpression : public IExpression {
        unique_ptr<IExpression> size;

        inline NewIntArrayExpression(const Location& location, IExpression* expression)
            : IExpression(location), size(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NewExpression : public IExpression {
        string classId;

        inline NewExpression(const Location& location, const string& id)
            : IExpression(location), classId(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NegateExpression : public IExpression {
        unique_ptr<IExpression> expression;

        inline NegateExpression(const Location& location, IExpression* newExpr)
            : IExpression(location), expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}