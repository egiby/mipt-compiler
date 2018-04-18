#include <irt/expressions/Binop.h>
#include <irt/expressions/Call.h>
#include <irt/expressions/Const.h>
#include <irt/expressions/ESeq.h>
#include <irt/expressions/Mem.h>
#include <irt/expressions/Name.h>
#include <irt/expressions/Temp.h>

#include <irt/statements/CJump.h>
#include <irt/statements/Exp.h>
#include <irt/statements/Jump.h>
#include <irt/statements/Label.h>
#include <irt/statements/Move.h>
#include <irt/statements/Seq.h>

#include <irt/IIRVisitor.h>

namespace NIRTree {
    void Binop::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Call::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Const::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void ESeq::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Mem::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Name::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Temp::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }
}
