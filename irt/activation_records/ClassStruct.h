#pragma once

#include <irt/NodeTypes.h>

#include <symbol_table/MethodInfo.h>
#include <symbol_table/ClassInfo.h>

#include <vector>

namespace NIRTree {
    interface IClassStruct {
        virtual ~IClassStruct() = default;

        virtual const std::string& GetTableName() const = 0;

        virtual IExp* GetFieldFrom(const Symbol* fieldName, IExp* base, const Location& location) const = 0;
        virtual IExp* GetVirtualMethodAddress(const Symbol* methodName,
                                              IExp* base, const Location& location) const = 0;
        virtual IExp* AllocateNew(const Location& location) const = 0;
    };

    interface IClassStructBuilder {
        virtual ~IClassStructBuilder() = default;

        virtual IClassStruct* GetClassStruct(const NSymbolTable::ClassInfo& info, const NSymbolTable::SymbolTable&) const = 0;
    };
}