#pragma once

#include "common.h"

#include "INode.h"
#include "Statement.h"
#include "Type.h"
#include "VarDeclaration.h"

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

        string nameId;
        vector<std::pair<Type, string>> args;

        unique_ptr<vector<unique_ptr<VarDeclaration>>> localVars;
        unique_ptr<vector<unique_ptr<IStatement>>> statements;
        
        unique_ptr<IExpression> returnExpression;

        inline MethodDeclaration(const Location& location
            , Type type
            , const string& name
            , const vector<std::pair<Type, string>>& args
            , vector<unique_ptr<VarDeclaration>>* vars
            , vector<unique_ptr<IStatement>>* statements
            , IExpression* expression)
            : INode(location), returnType(type), nameId(name), args(args), localVars(vars), statements(statements), returnExpression(expression) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}