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
        return static_cast<int>(formalIds.size());
    }

    std::shared_ptr<const IAccess> X86MiniJavaFrame::GetFormal(int index) {
        return idToAccess[formalIds[index]];
    }

    std::shared_ptr<const IAccess> X86MiniJavaFrame::GetFormalOrLocal(const NUtil::Symbol *id) {
        return idToAccess[id];
    }

    int X86MiniJavaFrame::TypeSize(const NSymbolTable::TypeInfo &type) const {
        // TODO: change to some valid implementation
        return 4;
    }
}