#pragma once

#include <symbol_table/SymbolTable.h>
#include <symbol_table/ClassInfo.h>
#include <symbol_table/Exceptions.h>

namespace NTypeChecker {
    void CheckDependencies(const NSymbolTable::SymbolTable& symbolTable);

    void CheckInClass(const NSymbolTable::SymbolTable& symbolTable,
        const NUtil::Symbol* superClassId,
        const NSymbolTable::ClassInfo& childClassInfo);
}