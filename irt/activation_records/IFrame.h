#pragma once

#include "IAccess.h"

#include <symbol_table/VariableInfo.h>

#include <memory>

namespace NIRTree {
    interface IFrame {
        virtual void AddLocal(const NSymbolTable::VariableInfo&) = 0;
        virtual void AddFormal(const NSymbolTable::VariableInfo&) = 0;
        virtual int GetFormalsCount() const = 0;
        virtual std::shared_ptr<const IAccess> GetFormal(int index) const = 0;
        virtual std::shared_ptr<const IAccess> GetFormalOrLocal(const NUtil::Symbol *name) const = 0;
        virtual int TypeSize(const NSymbolTable::TypeInfo&) const = 0;

        virtual ~IFrame() = default;
    };
}