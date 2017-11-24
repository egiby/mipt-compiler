#pragma once

#include "common.h"

#include "INode.h"
#include "Statement.h"
#include "Type.h"
#include "VarDeclaration.h"
#include <util/Symbol.h>

#include <memory>
#include <vector>
#include <string>

namespace NSyntaxTree {
    enum EModifier {
        PUBLIC,
        PRIVATE
    };

    struct MethodDeclaration : public INode {
        Type returnType;
        EModifier modifier = PUBLIC;

        const NUtil::Symbol* id;
        unique_ptr<vector<unique_ptr<VarDeclaration>>> args;

        unique_ptr<vector<unique_ptr<VarDeclaration>>> localVars;
        unique_ptr<vector<unique_ptr<IStatement>>> statements;
        
        unique_ptr<IExpression> returnExpression;

        inline MethodDeclaration(const Location& location
            , Type type
            , const NUtil::Symbol* name
            , vector<unique_ptr<VarDeclaration>>* args
            , vector<unique_ptr<VarDeclaration>>* vars
            , vector<unique_ptr<IStatement>>* statements
            , IExpression* expression)
            : INode(location), returnType(type), id(name), args(args), localVars(vars), statements(statements), returnExpression(expression) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}