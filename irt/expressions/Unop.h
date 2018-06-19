#pragma once

#include "IExp.h"

namespace NIRTree {
    class Unop : public IExp {
    public:
        enum EUnopType {
            NOT = 0,
        };

        Unop(EUnopType type, IExp *expression, const Location &location)
            : IExp(location), type(type), expression(expression) {
        }

        EUnopType type;
        std::unique_ptr<IExp> expression;

        void Accept(IIRVisitor *visitor) const override;
    };
}