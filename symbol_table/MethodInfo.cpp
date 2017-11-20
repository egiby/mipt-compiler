#include "MethodInfo.h"

namespace NSymbolTable {
    MethodInfo::MethodInfo(const Symbol* _methodId
        , Location _location
        , TypeInfo _returnType
        , NSyntaxTree::EModifier _modifier)
        : IdentifierInfo(_methodId, _location), returnType(_returnType), modifier(_modifier) {
    }

    void MethodInfo::InsertArgumentInfo(const VariableInfo& argInfo) {
        if (argsInfo.find(argInfo.GetId()) != argsInfo.end()) {

        }

        argsInfo[argInfo.GetId()] = argInfo;
    }

    void MethodInfo::InsertVariableInfo(const VariableInfo& varInfo) {
        varsInfo[varInfo.GetId()] = varInfo;
    }
}