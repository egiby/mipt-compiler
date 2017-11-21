#include "ClassInfo.h"

namespace NSymbolTable {
    ClassInfo::ClassInfo(const Symbol* _classId, const NSyntaxTree::Location& _location, const Symbol* _superClassId)
        : IdentifierInfo(_classId, _location), superClassId(_superClassId) {
    }

    void ClassInfo::InsertVarInfo(const VariableInfo& varInfo) {
        varsInfo.insert({varInfo.GetId(), varInfo});
    }

    void ClassInfo::InsertMethodInfo(const MethodInfo& methodInfo) {
        methodsInfo.insert({methodInfo.GetId(), methodInfo});
    }
}