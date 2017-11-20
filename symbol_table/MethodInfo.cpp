#include "MethodInfo.h"

namespace NSymbolTable {
    MethodInfo::MethodInfo(std::string _methodId, NSyntaxTree::Location _location, TypeInfo _returnType,
             NSyntaxTree::EModifier _modifier) : Symbol(_methodId),
                                                 location(_location),
                                                 returnType(_returnType),
                                                 modifier(_modifier) {}

    void MethodInfo::InsertArgumentInfo(const VariableInfo *argInfo) {
        argsInfo.push_back(argInfo);
    }

    void MethodInfo::InsertVariableInfo(const VariableInfo *varInfo) {
        varsInfo.push_back(varInfo);
    }

    
}