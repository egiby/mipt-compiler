#pragma once

#include "IAccess.h"

#include <symbol_table/VariableInfo.h>

namespace NIRTree {
    interface IFrame {
        virtual void AddLocal(const NSymbolTable::VariableInfo&) = 0;
        virtual void AddFormal(const NSymbolTable::VariableInfo&) = 0;

        virtual ~IFrame() {
        }
    };
}