#pragma once

#include <location.hh>

#include <ast/tree/INode.h>

namespace NSyntaxTree {
    inline Position ConvertPosition(const yy::position& pos) {
        return {pos.line, pos.column};
    }

    inline Location ConvertLocation(const yy::location& loc) {
        return {ConvertPosition(loc.begin), ConvertPosition(loc.end)};
    }
}