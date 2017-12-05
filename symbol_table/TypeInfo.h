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
        explicit TypeInfo(NSyntaxTree::EType _type, const Symbol *_classId = nullptr) noexcept;

        TypeInfo(const NSyntaxTree::Type &_type) : type(_type.type), classId(_type.id) {
        }

        const NSyntaxTree::EType& GetType() const { return type; }
        const Symbol* GetClassId() const;

        bool operator==(const TypeInfo& t) const;
        bool operator!=(const TypeInfo& t) const;

        std::string ToString() const;
    };

    using NSyntaxTree::INT;
    using NSyntaxTree::INT_ARRAY;
    using NSyntaxTree::BOOL;
    using NSyntaxTree::CLASS;

    const static TypeInfo IntType = TypeInfo(NSyntaxTree::INT);
    const static TypeInfo IntArrayType = TypeInfo(NSyntaxTree::INT_ARRAY);
    const static TypeInfo BooleanType = TypeInfo(NSyntaxTree::BOOL);
}