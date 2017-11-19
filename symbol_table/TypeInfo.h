#pragma once

#include "StringInterner.h"
#include "ast/tree/Type.h"

namespace NSymbolTable {
    class TypeInfo {
        NSyntaxTree::EType type;
        Symbol *classId;
    public:
        TypeInfo(NSyntaxTree::EType _type, Symbol *_classId);
        NSyntaxTree::EType GetType() const { return type; }
        const Symbol* GetClassId() const;
    };
}