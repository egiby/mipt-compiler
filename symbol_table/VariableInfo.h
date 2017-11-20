#pragma once

#include "common.h"
#include "IdentifierInfo.h"
#include "TypeInfo.h"

#include <ast/tree/INode.h>
#include <util/Symbol.h>

namespace NSymbolTable {
    class VariableInfo : public IdentifierInfo {
        TypeInfo typeInfo;

    public:
        VariableInfo(const Symbol* _varName, const Location& _location, const TypeInfo& _typeInfo);
        const TypeInfo& GetTypeInfo() const { return typeInfo; }
    };
}