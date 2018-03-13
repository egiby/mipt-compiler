#pragma once

#include "IFrame.h"

#include <vector>

namespace NIRTree {
    class X86MiniJavaFrame: public IFrame {
        std::vector<const NUtil::Symbol*> formalIds;
        std::unordered_map<const NUtil::Symbol*, std::shared_ptr<const IAccess>> idToAccess;
        std::unordered_map<const NUtil::Symbol*, NSymbolTable::VariableInfo> idToInfo;
    public:
        void AddLocal(const NSymbolTable::VariableInfo &variable) override;
        void AddFormal(const NSymbolTable::VariableInfo &variable) override;
        int GetFormalsCount() const override;
        std::shared_ptr<const IAccess> GetFormal(int index) override;
        std::shared_ptr<const IAccess> GetFormalOrLocal(const NUtil::Symbol *id) override;
    };
}