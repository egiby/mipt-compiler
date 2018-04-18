#pragma once

#include "NodeTypes.h"

#include <util/CommonDefs.h>

namespace NIRTree {
    interface IIRVisitor {
        virtual void Visit(const Binop*) = 0;
        virtual void Visit(const Call*) = 0;
        virtual void Visit(const Const*) = 0;
        virtual void Visit(const ESeq*) = 0;
        virtual void Visit(const Mem*) = 0;
        virtual void Visit(const Name*) = 0;
        virtual void Visit(const Temp*) = 0;

        virtual void Visit(const CJump*) = 0;
        virtual void Visit(const Exp*) = 0;
        virtual void Visit(const Jump*) = 0;
        virtual void Visit(const Label*) = 0;
        virtual void Visit(const Move*) = 0;
        virtual void Visit(const Seq*) = 0;
    };
}