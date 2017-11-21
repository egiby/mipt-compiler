#include "TypeInfo.h"

#include <cassert>

namespace NSymbolTable {
    TypeInfo::TypeInfo(NSyntaxTree::EType _type, const Symbol *_classId) : type(_type) {
        if (type == NSyntaxTree::CLASS) {
            assert(_classId != nullptr);
            classId = _classId;
        }
    }

    const Symbol* TypeInfo::GetClassId() const {
        assert(type == NSyntaxTree::CLASS);
        return classId;
    }

    bool TypeInfo::operator==(const TypeInfo &t) const {
        return type == t.type && classId == t.classId;
    }

    bool TypeInfo::operator!=(const TypeInfo &t) const {
        return !(*this == t);
    }
}
