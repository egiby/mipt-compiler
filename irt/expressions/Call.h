#pragma once

#include <irt/List.h>

namespace NIRTree {
    class Call : public IExp {
    public:
        std::unique_ptr<const IExp> funcExp;
        std::unique_ptr<const ExpList> args;

        Call(const IExp *_funcExp, const ExpList *_args, const Location &_location)
            : IExp(_location), funcExp(_funcExp), args(_args) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };
}