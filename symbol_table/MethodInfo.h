#pragma once

#include "common.h"

#include "IdentifierInfo.h"
#include "TypeInfo.h"
#include "VariableInfo.h"

#include <ast/tree/MethodDeclaration.h>
#include <util/Symbol.h>

#include <vector>

namespace NSymbolTable {
    class MethodInfo : public IdentifierInfo {
        TypeInfo returnType;
        NSyntaxTree::EModifier modifier;
        std::unordered_map<const Symbol*, VariableInfo> argsInfo;
        std::unordered_map<const Symbol*, VariableInfo> varsInfo;

    public:
        MethodInfo(const Symbol* _methodId
                , Location _location
                , TypeInfo _returnType
                , NSyntaxTree::EModifier _modifier);

        void InsertArgumentInfo(const VariableInfo& argInfo);
        void InsertVariableInfo(const VariableInfo& varInfo);
            
        const TypeInfo& GetReturnType() const { return returnType; }
        NSyntaxTree::EModifier GetModifier() const { return modifier; }
        const std::unordered_map<const Symbol*, VariableInfo> &GetArgsInfo() const { return argsInfo; }
        const std::unordered_map<const Symbol*, VariableInfo> &GetVarsInfo() const { return varsInfo; }
    };
}