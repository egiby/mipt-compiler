#pragma once

#include "INode.h"
#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

namespace NIRTree {
    template <typename T>
    class List : public T {
    public:
        std::unique_ptr<const T> head;
        std::unique_ptr<const T> tail;
        NSyntaxTree::Location location;

        List(const T *_head, const T *_tail, const NSyntaxTree::Location &_location)
            : head(_head), tail(_tail), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
    };

    typedef List<IExp> ExpList;
    typedef List<IStm> StmList;
}