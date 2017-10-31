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
    protected:
        void Accept(const IVisitor *visitor) override;
    };
}