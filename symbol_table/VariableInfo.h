#pragma once

#include "TypeInfo.h"
#include "ast/tree/INode.h"

namespace NSymbolTable {
    class VariableInfo : public Symbol {
        TypeInfo typeInfo;
        NSyntaxTree::Location location;
    public:
        VariableInfo(std::string _varName, NSyntaxTree::Location _location, TypeInfo _typeInfo);
        const TypeInfo& GetTypeInfo() const { return typeInfo; }
    };
}