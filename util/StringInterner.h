#pragma once

#include <unordered_map>

namespace NUtil {
    class Symbol;

    class StringInterner {
        std::unordered_map<std::string, Symbol*> allStrings;
    public:
        Symbol* GetIntern(const std::string& src);
        ~StringInterner();
    };
}