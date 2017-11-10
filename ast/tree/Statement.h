#pragma once

#include "common.h"

#include "Expression.h"
#include "INode.h"

#include <memory>

namespace NSyntaxTree {
    interface IStatement : public INode {
    };

    struct Statements : public IStatement {
        unique_ptr<vector<unique_ptr<IStatement>>> statements;

        inline explicit Statements(vector<unique_ptr<IStatement>>* newStatements) : statements(newStatements) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IfStatement : public IStatement {
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;

        inline IfStatement(IExpression* expression
            , IStatement* newTrueStatement
            , IStatement* newFalseStatement) 
            : condition(expression), trueStatement(newTrueStatement), falseStatement(newFalseStatement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct WhileStatement : public IStatement {
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;
        
        inline WhileStatement(IExpression* expression, IStatement* statement) 
            : condition(expression), trueStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct PrintlnStatement : public IStatement {
        unique_ptr<IExpression> toPrint;

        inline explicit PrintlnStatement(IExpression* expression) : toPrint(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct AssignStatement : public IStatement {
        string lvalue;
        unique_ptr<IExpression> rvalue;

        inline AssignStatement(string id, IExpression* expression) : lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAssignmentStatement : public IStatement {
        string arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;

        inline ArrayElementAssignmentStatement(string id
            , IExpression* indexExpr
            , IExpression* rvalueExpr)
            : arrayId(id), index(indexExpr), rvalue(rvalueExpr) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}