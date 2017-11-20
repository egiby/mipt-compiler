#include "ClassInfo.h"

namespace NSymbolTable {
    ClassInfo::ClassInfo(std::string _classId, NSyntaxTree::Location _location, std::string _superClassId) :
        Symbol(_classId), location(_location) {
        superClassId = stringInterner.getIntern(_superClassId);
    }

    void ClassInfo::InsertVarInfo(const VariableInfo *varInfo) {
        varsInfo.push_back(varInfo);
    }

    void ClassInfo::InsertMethodInfo(const MethodInfo *methodInfo) {
        methodsInfo.push_back(methodInfo);
    }

}