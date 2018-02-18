#include "VariableInfo.h"

namespace NSymbolTable {
    VariableInfo::VariableInfo(const Symbol* _varName, const Location& _location, const TypeInfo& _typeInfo) :
        IdentifierInfo(_varName, _location), typeInfo(_typeInfo) {}

    VariableInfo::VariableInfo(const VariableInfo &info) :
        IdentifierInfo(info.id, info.location), typeInfo(info.typeInfo) {}
}