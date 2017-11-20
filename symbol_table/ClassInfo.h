#pragma once

#include "common.h"

#include "IdentifierInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"

#include <util/Symbol.h>

#include <unordered_map>

namespace NSymbolTable {
    class ClassInfo : public IdentifierInfo {
        std::unordered_map<const Symbol*, VariableInfo> varsInfo;
        std::unordered_map<const Symbol*, MethodInfo> methodsInfo;
        const Symbol *superClassId;

    public:
        ClassInfo(const Symbol* _classId, const NSyntaxTree::Location& _location, const Symbol* _superClassId = nullptr);

        void InsertVarInfo(const VariableInfo& varInfo);
        void InsertMethodInfo(const MethodInfo& methodInfo);

        const std::unordered_map<const Symbol*, VariableInfo>& GetVarsInfo() const { return varsInfo; }
        const std::unordered_map<const Symbol*, MethodInfo>& GetMethodsInfo() const { return methodsInfo; }
        const Symbol* GetSuperClassId() { return superClassId; }
    };
}