#pragma once

#include <vector>

#include "Symbol.h"
#include "VariableInfo.h"
#include "MethodInfo.h"

namespace NSymbolTable {
    static StringInterner stringInterner;

    class ClassInfo : public Symbol {
        NSyntaxTree::Location location;
        std::vector<const Symbol*> varsInfo;
        std::vector<const Symbol*> methodsInfo;
        const Symbol *superClassId;

    public:
        ClassInfo(std::string _classId, NSyntaxTree::Location _location, std::string _superClassId);
        void InsertVarInfo(const VariableInfo *varInfo);
        void InsertMethodInfo(const MethodInfo *methodInfo);    

        NSyntaxTree::Location GetLocation() { return location; }
        std::vector<const Symbol*> GetVarsInfo() { return varsInfo; }
        std::vector<const Symbol*> GetMethodsInfo() { return methodsInfo; }
        const Symbol* GetSuperClassId() { return superClassId;  }
    };
}