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

        vector<VarDeclaration> varDeclarations;
        vector<MethodDeclaration> methodDeclarations;
    protected:
        void Accept(const IVisitor *visitor) override;
    };

    struct MainClass : public INode {
        string nameId;
        string mainArgsId;

        unique_ptr<IStatement> mainStatement;
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}