#include "Program.h"
#include "IVisitor.h"

namespace NSyntaxTree {
    void Program::Accept(const IVisitor *visitor) {
        visitor->Visit(this);
    }
}