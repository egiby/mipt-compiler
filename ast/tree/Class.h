#pragma once

#include "common.h"

#include "INode.h"
#include "MethodDeclaration.h"
#include "VarDeclaration.h"
#include "Statement.h"
#include <util/Symbol.h>

#include <memory>
#include <string>
#include <vector>
namespace NSyntaxTree {
    struct ClassDeclaration : public INode {
        const NUtil::Symbol* id;
        const NUtil::Symbol* extendsId;

        unique_ptr<vector<unique_ptr<VarDeclaration>>> varDeclarations;
        unique_ptr<vector<unique_ptr<MethodDeclaration>>> methodDeclarations;
        
        inline ClassDeclaration(const Location& location
            , const NUtil::Symbol* name
            , const NUtil::Symbol* extends
            , vector<unique_ptr<VarDeclaration>>* vars
            , vector<unique_ptr<MethodDeclaration>>* methods) 
            : INode(location), id(name), extendsId(extends), varDeclarations(vars), methodDeclarations(methods) {
            }

        void Accept(IVisitor *visitor) const override;
    };

    struct MainClass : public INode {
        const NUtil::Symbol* nameId;
        const NUtil::Symbol* mainArgsId;

        unique_ptr<IStatement> mainStatement;

        inline MainClass(const Location& location
            , const NUtil::Symbol* name
            , const NUtil::Symbol* args
            , IStatement* statement)
            : INode(location), nameId(name), mainArgsId(args), mainStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}