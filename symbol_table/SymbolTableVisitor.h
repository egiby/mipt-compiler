#pragma once

#include "common.h"

#include <ast/tree/visitors/IVisitor.h>
#include <util/StringInterner.h>

namespace NSymbolTable {
    class SymbolTableVisitor : public NSyntaxTree::IVisitor {
        std::unique_ptr<StringInterner> interner;
    public:
//        void CreateSymbolTable()
    };
}