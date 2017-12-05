#pragma once

#include "SymbolTable.h"

#include <ast/tree/NodeTypes.h>

namespace NSymbolTable {
    SymbolTable BuildSymbolTable(const NSyntaxTree::Program &program);
}
