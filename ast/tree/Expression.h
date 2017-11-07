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
            , unique_ptr<IExpression> leftExp
            , unique_ptr<IExpression> rightExp) 
            : type(expType), left(std::move(leftExp)), right(std::move(rightExp)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAccessExpression : public IExpression {
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;

        ArrayElementAccessExpression(unique_ptr<IExpression> arrayExpr, unique_ptr<IExpression> indexExpr) 
            : array(std::move(arrayExpr)), index(std::move(indexExpr)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayLengthExpression : public IExpression {
        unique_ptr<IExpression> array;
        
        inline explicit ArrayLengthExpression(unique_ptr<IExpression> expression) : array(std::move(expression)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct MethodCallExpression : public IExpression {
        unique_ptr<IExpression> object;
        string nameId;
        vector<unique_ptr<IExpression>> args;

        inline MethodCallExpression(unique_ptr<IExpression> objectExpr, const string& name, vector<unique_ptr<IExpression>> argsVector) 
            : object(std::move(objectExpr)), nameId(name), args(std::move(argsVector)) {
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

        inline explicit NewIntArrayExpression(unique_ptr<IExpression> expression) : size(std::move(expression)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NewExpression : public IExpression {
        string classId;

        inline explicit NewExpression(const string& id) classId(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct NegateExpression : public IExpression {
        unique_ptr<IExpression> expression;

        inline explicit NegateExpression(unique_ptr<IExpression> newExpr) : expression(std::move(newExpr)) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}