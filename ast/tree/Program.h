#pragma once

#include "common.h"

#include "INode.h"
#include "Class.h"

#include <vector>
#include <memory>

namespace NSyntaxTree {
    struct Program : public INode {
        unique_ptr<MainClass> mainClass;
        vector<std::unique_ptr<ClassDeclaration>> classes;

        void Accept(IVisitor *visitor) const override;
    };
}