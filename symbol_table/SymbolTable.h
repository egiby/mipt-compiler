#pragma once

#include "common.h"

#include "ClassInfo.h"

#include <util/StringInterner.h>

#include <memory>
#include <unordered_map>

namespace NSymbolTable {

    class SymbolTable {
        std::unordered_map<const Symbol*, ClassInfo> classes;
        const Symbol* mainClass; // TODO: what should we do with main class?
    public:
        bool HasClass(const Symbol* id) const;
        const ClassInfo& GetClassInfo(const Symbol* id) const;

        const std::unordered_map<const Symbol*, ClassInfo>& GetClasses() const;

        void InsertClassInfo(const ClassInfo&);
        void SetMainClass(const Symbol*);

        const Symbol* GetMainClassId() const;
    };
}