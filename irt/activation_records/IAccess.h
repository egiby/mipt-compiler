#pragma once

#include <util/CommonDefs.h>
#include <irt/expressions/Temp.h>
#include <irt/expressions/IExp.h>

namespace NIRTree {
    interface IAccess {
        enum ERecordsType {
            FORMAL,
            LOCAL,
            FP,
            SP,
            ADDRESS_EXIT,
            ADDRESS_RETURN_VALUE
        };

        virtual const ERecordsType GetRecordType() = 0;
        virtual const int GetSize() const = 0;
        virtual IExp* GetExp(Temp* fp, const Location& location) const = 0;

        virtual ~IAccess() = default;
    };
}
