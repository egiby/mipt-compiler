#pragma once

#include "common.h"

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
        RedefinitionException(const Location& currentLoc
            , const Symbol* currentId
            , const Location& shadowedLoc)
            : SymbolTableException("Redefinition: " + currentId->String()
                                   + " on " + currentLoc.ToString() + " shadows " + shadowedLoc.ToString()) {}
    };

    class CyclicDependencyException : public SymbolTableException {
    public:
        CyclicDependencyException(const Location& loc, const Symbol* id)
            : SymbolTableException("Cyclic dependency: " + id->String() + " on " + loc.ToString()) {}
    };

    class NonDeclaredSymbolException : public SymbolTableException {
    public:
        NonDeclaredSymbolException(const Location& loc, const Symbol* id)
            : SymbolTableException("Identifier is not declared: " + id->String() + " on " + loc.ToString()) {}
    };
}