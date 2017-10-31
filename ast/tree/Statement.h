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
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct IfStatement : public IStatement {
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct WhileStatement : public IStatement {
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct PrintlnStatement : public IStatement {
        unique_ptr<IExpression> toPrint;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct AssignStatement : public IStatement {
        string lvalue;
        unique_ptr<IExpression> rvalue;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct ArrayElementAssignmentStatement : public IStatement {
        string arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}