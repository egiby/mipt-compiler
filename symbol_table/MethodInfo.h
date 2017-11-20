#pragma once
#include "Symbol.h"
#pragma once

#include <vector>

#include "TypeInfo.h"
#include "Symbol.h"
#include "ast/tree/MethodDeclaration.h"
#include "VariableInfo.h"

namespace NSymbolTable {
    class MethodInfo : public Symbol {
        NSyntaxTree::Location location;
        TypeInfo returnType;
        NSyntaxTree::EModifier modifier;
        std::vector<const Symbol*> argsInfo;
        std::vector<const Symbol*> varsInfo;

    public:
        MethodInfo(std::string _methodId, NSyntaxTree::Location _location, TypeInfo _returnType,
             NSyntaxTree::EModifier _modifier);

        void InsertArgumentInfo(const VariableInfo *argInfo);
        void InsertVariableInfo(const VariableInfo *varInfo);
            
        TypeInfo GetReturnType() const { return returnType; }
        NSyntaxTree::EModifier GetModifier() const { return modifier; }
        const std::vector<const Symbol*> &GetArgsInfo() const { return argsInfo; }
        const std::vector<const Symbol*> &GetVarsInfo() const { return varsInfo; }


    };
}