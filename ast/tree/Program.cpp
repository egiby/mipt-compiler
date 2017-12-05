#include "Program.h"
#include "visitors/IVisitor.h"

namespace NSyntaxTree {
    void Program::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}