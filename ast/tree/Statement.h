#pragma once

#include "common.h"

#include "Expression.h"
#include "INode.h"

#include <memory>

namespace NSyntaxTree {
    interface IStatement : public INode {
    };

    struct Statements : public IStatement {
        vector<unique_ptr<IStatement>> statements;

        inline explicit Statements(vector<unique_ptr<IStatement>> newStatements) : statements(std::move(newStatements)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IfStatement : public IStatement {
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;

        inline IfStatement(unique_ptr<IExpression> expression
            , unique_ptr<IStatement> newTrueStatement
            , unique_ptr<IStatement> newFalseStatement) 
            : condition(std::move(expression)), trueStatement(std::move(newTrueStatement)), falseStatement(std::move(newFalseStatement)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct WhileStatement : public IStatement {
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;
        
        inline WhileStatement(unique_ptr<IExpression> expression, unique_ptr<IStatement> statement) 
            : condition(std::move(expression)), trueStatement(std::move(statement)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct PrintlnStatement : public IStatement {
        unique_ptr<IExpression> toPrint;

        inline explicit PrintlnStatement(unique_ptr<IExpression> expression) : toPrint(std::move(expression)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct AssignStatement : public IStatement {
        string lvalue;
        unique_ptr<IExpression> rvalue;

        inline AssignStatement(string id, unique_ptr<IExpression> expression) : lvalue(id), rvalue(std::move(expression)) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAssignmentStatement : public IStatement {
        string arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;

        inline ArrayElementAssignmentStatement(string id
            , unique_ptr<IExpression> indexExpr
            , unique_ptr<IExpression> rvalueExpr)
            : arrayId(id), index(std::move(indexExpr)), rvalue(std::move(rvalueExpr)) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}