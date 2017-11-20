#pragma once

#include "common.h"

#include "ClassInfo.h"

#include <util/StringInterner.h>

#include <memory>
#include <unordered_map>

namespace NSymbolTable {

    class SymbolTable {
        std::unique_ptr<StringInterner> interner;
        std::unordered_map<const Symbol*, ClassInfo> classes;
    public:

    };
}