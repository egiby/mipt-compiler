#pragma once

#include "common.h"

#include "IdentifierInfo.h"

#include <ast/tree/Type.h>
#include <util/StringInterner.h>

namespace NSymbolTable {
    class TypeInfo {
        NSyntaxTree::EType type;
        const Symbol *classId;
    public:
        explicit TypeInfo(NSyntaxTree::EType _type, const Symbol *_classId = nullptr);
        const NSyntaxTree::EType& GetType() const { return type; }
        const Symbol* GetClassId() const;

        bool operator==(const TypeInfo& t) const;
        bool operator!=(const TypeInfo& t) const;
    };
}