#pragma once

#include "IAccess.h"

namespace NIRTree {
    class InRegAccess: public IAccess {
    public:
        ERecordsType GetRecordType() override {
            return recordType;
        }

        int GetSize() const override {
            return size;
        }

        IExp* GetExp(Temp* fp, const Location& location) const override;

    private:
        const int size;
        const ERecordsType recordType;
        int id;
        const std::string name;
        std::unique_ptr<Temp> temp;
    };
}