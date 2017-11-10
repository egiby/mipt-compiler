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

        unique_ptr<vector<unique_ptr<VarDeclaration>>> varDeclarations;
        unique_ptr<vector<unique_ptr<MethodDeclaration>>> methodDeclarations;
        
        inline ClassDeclaration(const string &name
            , const string &extends
            , vector<unique_ptr<VarDeclaration>>* vars
            , vector<unique_ptr<MethodDeclaration>>* methods) 
            : nameId(name), extendsId(extends), varDeclarations(vars), methodDeclarations(methods) {
            }

        void Accept(IVisitor *visitor) const override;
    };

    struct MainClass : public INode {
        string nameId;
        string mainArgsId;

        unique_ptr<IStatement> mainStatement;

        inline MainClass(const std::string& name, const std::string& args, IStatement* statement) 
            : nameId(name), mainArgsId(args), mainStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}