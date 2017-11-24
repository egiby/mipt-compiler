#pragma once

#include "common.h"

#include "INode.h"
#include "Class.h"
#include <util/StringInterner.h>

#include <vector>
#include <memory>

namespace NSyntaxTree {
    struct Program : public INode {
        unique_ptr<MainClass> mainClass;
        unique_ptr<vector<std::unique_ptr<ClassDeclaration>>> classes;
        std::shared_ptr<NUtil::StringInterner> interner;

        void Accept(IVisitor *visitor) const override;
    };
}