#pragma once

#include "INode.h"
#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

namespace NIRTree {
    // T should has field location
    template <typename T>
    class List : public T {
    public:
        std::unique_ptr<const T> head;
        std::unique_ptr<const T> tail;

        List(const T *_head, const T *_tail, const NSyntaxTree::Location &_location)
            : head(_head), tail(_tail), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };

    using ExpList = List<IExp>;
    using StmList = List<IStm>;
}