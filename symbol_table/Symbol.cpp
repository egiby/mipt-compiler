#include "Symbol.h"

namespace NSymbolTable {
    bool Symbol::operator==(const Symbol &symbol) {
        return &symbol == this;
    }

    bool Symbol::operator!=(const Symbol &symbol) {
        return &symbol != this;
    }

    Symbol::Symbol(const std::string s) {
        string = std::unique_ptr<std::string>{new std::string(s)};
    }
}