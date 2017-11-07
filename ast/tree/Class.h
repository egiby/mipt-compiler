#pragma once

#include "common.h"

#include "INode.h"
#include "MethodDeclaration.h"
#include "VarDeclaration.h"
#include "Statement.h"

#include <memory>
#include <string>
#include <vector>
namespace NSyntaxTree {
    struct ClassDeclaration : public INode {
        string nameId;
        string extendsId;

        vector<unique_ptr<VarDeclaration>> varDeclarations;
        vector<unique_ptr<MethodDeclaration>> methodDeclarations;
        
        inline ClassDeclaration(const string &name
            , const string &extends
            , vector<unique_ptr<VarDeclaration>> vars
            , vector<unique_ptr<MethodDeclaration>> methods) 
            : nameId(name), extendsId(extends), varDeclarations(std::move(vars)), methodDeclarations(std::move(methods)) {
            }

        void Accept(IVisitor *visitor) const override;
    };

    struct MainClass : public INode {
        string nameId;
        string mainArgsId;

        unique_ptr<IStatement> mainStatement;

        inline MainClass(const std::string& name, const std::string& args, unique_ptr<IStatement> statement) 
            : nameId(name), mainArgsId(args), mainStatement(std::move(statement)) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}