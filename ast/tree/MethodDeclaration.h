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
    struct MethodDeclaration : public INode {
        Type returnType;

        string nameId;
        vector<std::pair<Type, string>> args;

        vector<unique_ptr<VarDeclaration>> localVars;
        vector<unique_ptr<IStatement>> statements;
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}