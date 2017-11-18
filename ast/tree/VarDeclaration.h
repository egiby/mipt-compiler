#pragma once

#include "common.h"

#include "INode.h"
#include "Type.h"

#include <string>

namespace NSyntaxTree {
    struct VarDeclaration : public INode {
        Type type;
        string id;

        inline VarDeclaration(const Location& location, const Type& type, const string& id)
            : INode(location), type(type), id(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}