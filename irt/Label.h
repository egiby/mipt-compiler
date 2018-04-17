#pragma once

#include <util/StringInterner.h>

namespace NIRTree {
    using Label = NUtil::Symbol;

    class LabelHolder {
        static Label * GetLabel(const std::string &name);
        static Label * GetNextLabel();

    private:
        static int nextId;
        static std::string labelPrefix;

        static NUtil::StringInterner interner;
    };
}