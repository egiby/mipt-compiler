#pragma once

#include <irt/List.h>

namespace NIRTree {
    class Call : public IExp {
    public:
        std::unique_ptr<const IExp> funcExp;
        std::unique_ptr<const ExpList> args;
        NSyntaxTree::Location location;

        Call(const IExp *_funcExp, const ExpList *_args, const NSyntaxTree::Location &_location)
            : funcExp(_funcExp), args(_args), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };
}