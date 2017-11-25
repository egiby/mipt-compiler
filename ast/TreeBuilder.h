#pragma once

#include <ast/tree/NodeTypes.h>
#include <util/StringInterner.h>

namespace NSyntaxTree {
    Program BuildTree(std::istream *input);
}