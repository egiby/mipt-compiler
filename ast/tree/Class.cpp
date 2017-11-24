#include "Class.h"
#include "visitors/IVisitor.h"

namespace NSyntaxTree {
    void ClassDeclaration::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }

    void MainClass::Accept(IVisitor *visitor) const {
        std::cout << "This is mainClass accept method" << std::endl;
        visitor->Visit(this);
    }
}