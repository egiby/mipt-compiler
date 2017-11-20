#pragma once

#include <unordered_map>

namespace NUtil {
    class Symbol;

    class StringInterner {
        std::unordered_map<std::string, Symbol*> allStrings;
    public:
        Symbol* getIntern(const std::string& src);
        ~StringInterner();
    };
}