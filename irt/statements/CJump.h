#pragma once

#include "IStm.h"
#include "Label.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class CJump : public IStm {
        int relop; //??
        std::unique_ptr<const IExp> leftExp;
        std::unique_ptr<const IExp> rightExp;
        // label iftrue
        // label iffalse
    };
}