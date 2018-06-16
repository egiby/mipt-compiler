#include "InFrameAccess.h"
#include <irt/NodeTypes.h>

namespace NIRTree {

    IExp *InFrameAccess::GetExp(Temp *fp, const Location &location) const {
        return new Mem(new Binop(PLUS, fp, new Const(offset, location), location), location);
    }

    InFrameAccess::InFrameAccess(IAccess::ERecordsType type, int size, int offset)
            : recordType(recordType), size(size), offset(offset) {
    }


}
