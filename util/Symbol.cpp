#include "Symbol.h"

namespace NUtil {
    Symbol::Symbol(const std::string& s) {
        string = std::make_unique<std::string>(s);
    }
}