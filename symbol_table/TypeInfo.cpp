#include "TypeInfo.h"
#include <cassert>

namespace NSymbolTable {
    TypeInfo::TypeInfo(NSyntaxTree::EType _type, Symbol *_classId) : type(_type) {
        if (type == NSyntaxTree::CLASS) {
            classId = _classId;
        }
    }

    const Symbol* TypeInfo::GetClassId() const {
        assert(type == NSyntaxTree::CLASS);
        return classId;
    }
}
