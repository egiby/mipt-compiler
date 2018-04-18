#pragma once

#include "IExp.h"

namespace NIRTree {
    class Temp : public IExp {
    public:
        enum TempType {
            ID,
            NAME
        };

        const int id;

        const int localId;
        const std::string name;
        TempType type;

        Temp(int localId, const Location &location);
        Temp(const std::string &name, const Location &location);

        void Accept(IIRVisitor *visitor) const override;
    private:
        static int counter;
    };
}