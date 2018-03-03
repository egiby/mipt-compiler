#pragma once

#include "IStm.h"
#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Move : public IStm {
    public:
        std::unique_ptr<const IExp> dist;
        std::unique_ptr<const IExp> src;
        NSyntaxTree::Location location;

        Move(const IExp *_dist, const IExp *_src, const NSyntaxTree::Location &_location)
            : dist(_dist), src(_src), location(_location) {
        }
            
        void Accept(IIRVisitor *visitor) const override;      
    };
}