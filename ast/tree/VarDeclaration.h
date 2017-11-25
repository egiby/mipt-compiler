#pragma once

#include "common.h"

#include "INode.h"
#include "Type.h"
#include <util/Symbol.h>

#include <string>

namespace NSyntaxTree {
    struct VarDeclaration : public INode {
        Type type;
        const NUtil::Symbol* id;

        inline VarDeclaration(const Location& location, const Type& type, const NUtil::Symbol* id)
            : INode(location), type(type), id(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}