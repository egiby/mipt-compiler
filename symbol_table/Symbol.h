#include <iostream>
#include <memory>

namespace NSymbolTable {
    class Symbol {
        std::unique_ptr<std::string> string;
    public:
        const std::string &String() const { return *(string); }

        Symbol(const std::string);
        Symbol(const Symbol&) = delete;
        void operator=(const Symbol&) = delete;

        bool operator==(const Symbol&);
        bool operator!=(const Symbol&);
    };
}