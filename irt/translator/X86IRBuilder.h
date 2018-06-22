#pragma once

#include <ast/tree/Program.h>
#include <symbol_table/SymbolTable.h>
#include <irt/NodeTypes.h>

namespace NIRTree {
    IRForest BuildTree(const NSyntaxTree::Program &program, const NSymbolTable::SymbolTable &symbolTable);
}