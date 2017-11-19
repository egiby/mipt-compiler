#include "VariableInfo.h"

namespace NSymbolTable {
    VariableInfo::VariableInfo(std::string _varName, NSyntaxTree::Location _location, TypeInfo _typeInfo) :
        Symbol(_varName), typeInfo(_typeInfo), location(_location) {}
}