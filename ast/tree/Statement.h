#pragma once

#include "common.h"

#include "Expression.h"
#include "INode.h"

#include <memory>

namespace NSyntaxTree {
    interface IStatement : public INode {
        inline explicit IStatement(const Location& location) : INode(location) {
        }
        IStatement() = default;
    };

    struct Statements : public IStatement {
        unique_ptr<vector<unique_ptr<IStatement>>> statements;

        inline Statements(const Location& location, vector<unique_ptr<IStatement>>* newStatements)
            : IStatement(location), statements(newStatements) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct IfStatement : public IStatement {
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;

        inline IfStatement(const Location& location
            , IExpression* expression
            , IStatement* newTrueStatement
            , IStatement* newFalseStatement) 
            : IStatement(location), condition(expression), trueStatement(newTrueStatement), falseStatement(newFalseStatement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct WhileStatement : public IStatement {
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;
        
        inline WhileStatement(const Location& location, IExpression* expression, IStatement* statement)
            : IStatement(location), condition(expression), trueStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct PrintlnStatement : public IStatement {
        unique_ptr<IExpression> toPrint;

        inline PrintlnStatement(const Location& location, IExpression* expression)
            : IStatement(location), toPrint(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct AssignStatement : public IStatement {
        string lvalue;
        unique_ptr<IExpression> rvalue;

        inline AssignStatement(const Location& location, const string& id, IExpression* expression)
            : IStatement(location), lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    struct ArrayElementAssignmentStatement : public IStatement {
        string arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;

        inline ArrayElementAssignmentStatement(const Location& location
            , const string& id
            , IExpression* indexExpr
            , IExpression* rvalueExpr)
            : IStatement(location), arrayId(id), index(indexExpr), rvalue(rvalueExpr) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}