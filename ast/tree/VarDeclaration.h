#pragma once

#include "common.h"

#include "INode.h"
#include "Type.h"

#include <string>

namespace NSyntaxTree {
    struct VarDeclaration : public INode {
        Type type;
        string id;
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}