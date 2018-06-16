#include "InRegAccess.h"

#include <irt/NodeTypes.h>

namespace NIRTree {
    IExp *InRegAccess::GetExp(NIRTree::Temp *fp, const NUtil::Location &location) const {
        delete fp;
        return new Mem(new Temp(*temp.get()), location);
    }
}
