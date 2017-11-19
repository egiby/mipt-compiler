#include "StringInterner.h"

namespace NSymbolTable {
    Symbol *StringInterner::getIntern(const std::string &src) {
        auto cached = allStrings.find(src);
        if (cached != allStrings.end()) {
            return cached->second;
        }
        Symbol *newVal = new Symbol(src);
        allStrings.insert({src, newVal});
        return newVal;
    }
}