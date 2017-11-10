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

        inline BinaryExpression(EBinaryExprType expType
            , IExpression* leftExp
            , IExpression* rightExp) 
            : type(expType), left(leftExp), right(rightExp) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAccessExpression : public IExpression {
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;

        ArrayElementAccessExpression(IExpression* arrayExpr, IExpression* indexExpr) 
            : array(arrayExpr), index(indexExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayLengthExpression : public IExpression {
        unique_ptr<IExpression> array;
        
        inline explicit ArrayLengthExpression(IExpression* expression) : array(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct MethodCallExpression : public IExpression {
        unique_ptr<IExpression> object;
        string nameId;
        unique_ptr<vector<unique_ptr<IExpression>>> args;

        inline MethodCallExpression(IExpression* objectExpr, const string& name, vector<unique_ptr<IExpression>>* argsVector) 
            : object(objectExpr), nameId(name), args(argsVector) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IntegerLiteralExpression : public IExpression {
        int value;

        inline explicit IntegerLiteralExpression(int value) : value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct BoolLiteralExpression : public IExpression {
        bool value;

        inline explicit BoolLiteralExpression(bool value) : value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IdentifierExpression : public IExpression {
        string identifier;

        inline explicit IdentifierExpression(const string& identifier) : identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ThisExpression : public IExpression {
        void Accept(IVisitor *visitor) const override;
    };

    struct NewIntArrayExpression : public IExpression {
        unique_ptr<IExpression> size;

        inline explicit NewIntArrayExpression(IExpression* expression) : size(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NewExpression : public IExpression {
        string classId;

        inline explicit NewExpression(const string& id) : classId(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NegateExpression : public IExpression {
        unique_ptr<IExpression> expression;

        inline explicit NegateExpression(IExpression* newExpr) : expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}