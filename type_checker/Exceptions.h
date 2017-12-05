#pragma once

#include <symbol_table/Exceptions.h>
#include <symbol_table/TypeInfo.h>

namespace NTypeChecker {
    class IllegalTypeException: public NSymbolTable::SymbolTableException {
    public:
        using NSymbolTable::SymbolTableException::SymbolTableException;

        IllegalTypeException(const NSyntaxTree::Location &loc
            , const NSymbolTable::TypeInfo &found
            , const NSymbolTable::TypeInfo &expected)
            : SymbolTableException("Error: expected " + expected.ToString() + ", found " + found.ToString()
                                   + " on " + loc.ToString()) {
        }

        IllegalTypeException(const NSyntaxTree::Location &loc
            , const NSymbolTable::TypeInfo &found
            /* expected non POD type */)
            : SymbolTableException("Error: expected object of some class, found " + found.ToString()
                                                 + " on " + loc.ToString()) {
        }
    };

    class BadArgumentsException: public NSymbolTable::SymbolTableException {
    public:
        using NSymbolTable::SymbolTableException::SymbolTableException;
        explicit BadArgumentsException(const NSyntaxTree::Location &loc)
            : SymbolTableException("Error: bad arguments on " + loc.ToString()) {
        }
    };

    class PrivateAccessException: public NSymbolTable::SymbolTableException {
    public:
        using NSymbolTable::SymbolTableException::SymbolTableException;
        PrivateAccessException(const NSyntaxTree::Location &loc
                , const NSymbolTable::Symbol* methodId
                , const NSymbolTable::Symbol* classId) : SymbolTableException("Unexpected access to private method "
                                                                              + methodId->String() + " of class "
                                                                              + classId->String() + " on "
                                                                              + loc.ToString()) {
        }
    };
}
