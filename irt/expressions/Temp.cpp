#include "Temp.h"

#include <util/Location.h>

namespace NIRTree {
    Temp::Temp(int localId, const Location &location)
        : IExp(location), id(counter++), localId(localId), name(""), type(ID) {
    }

    Temp::Temp(const std::string &name, const Location &location)
        : IExp(location), id(counter++), localId(-1), name(name), type(NAME) {
    }

    int Temp::counter = 0;
}
