#pragma once

#include <stdexcept>

namespace NSymbolTable {
    class SymbolTableException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    public:
        SymbolTableException(const std::string& message) : runtime_error(message) {
        }
    };

    class RedefinitionException : public SymbolTableException {
    public:

    };

    class CyclicDependencyException : public SymbolTableException {
    public:

    };
}