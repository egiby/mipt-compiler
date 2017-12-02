#pragma once

#include <symbol_table/SymbolTable.h>

namespace NTypeChecker {
    void CheckDependencies(const NSymbolTable::SymbolTable& symbolTable);
}