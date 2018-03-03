#pragma once

#include "IStm.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Jump : public IStm {
    public:
        std::unique_ptr<const IExp> exp;
        //targets

        //TODO
    };
}