#include "Class.h"
#include "IVisitor.h"

namespace NSyntaxTree {
    void ClassDeclaration::Accept(const IVisitor *visitor) {
        visitor->Visit(this);
    }

    void MainClass::Accept(const IVisitor *visitor) {
        visitor->Visit(this);
    }
}