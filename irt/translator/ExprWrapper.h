#pragma once

#include <irt/ISubtreeWrapper.h>

#include <irt/statements/Exp.h>

namespace NIRTree {
    class ExprWrapper: public ISubtreeWrapper {
    public:
        explicit ExprWrapper(IExp *expression) : expression(expression) {
            location = expression->location;
        }

        IExp * ToExp() override {
            return expression.release();
        }

        IStm * ToStm() override {
            return new Exp(expression.release(), location);
        }

        IStm * ToConditional(CJump::EJumpType type, const Label *trueLabel, const Label *falseLabel) override {
            return new CJump(type, expression.release(), new Temp(std::string("true"), Location()), trueLabel, falseLabel, location);
        };

        void Accept(IIRVisitor *visitor) const override;

    private:
        std::unique_ptr<IExp> expression;
    };
}