#include <unordered_map>
#include "Symbol.h"

namespace NSymbolTable {
    class StringInterner {
        std::unordered_map<std::string, Symbol*> allStrings;
    public:
        Symbol *getIntern(const std::string &src);
    };
}