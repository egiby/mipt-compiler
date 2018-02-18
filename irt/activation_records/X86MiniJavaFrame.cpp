#include "X86MiniJavaFrame.h"

namespace NIRTree {

    void X86MiniJavaFrame::AddLocal(const NSymbolTable::VariableInfo &variable) {
        idToInfo.insert({variable.GetId(), variable});
        idToAccess[variable.GetId()] = nullptr;
    }

    void X86MiniJavaFrame::AddFormal(const NSymbolTable::VariableInfo &variable) {
        formalIds.push_back(variable.GetId());

        idToInfo.insert({variable.GetId(), variable});
        idToAccess[variable.GetId()] = nullptr;
    }

    int X86MiniJavaFrame::GetFormalsCount() const {
        return formalIds.size();
    }

    std::shared_ptr<const IAccess> X86MiniJavaFrame::GetFormal(int index) {
        return idToAccess[formalIds[index]];
    }

    std::shared_ptr<const IAccess> X86MiniJavaFrame::GetFormalOrLocal(const NSymbolTable::Symbol *id) {
        return idToAccess[id];
    }
}