#pragma once

#include "StringInterner.h"

#include <iostream>
#include <memory>

namespace NUtil {
    class Symbol {
    public:
        const std::string& String() const { return *(string); }

        Symbol(const Symbol&) = delete;
        void operator=(const Symbol&) = delete;

        friend class StringInterner;
    private:
        Symbol(const std::string&);

        std::unique_ptr<std::string> string;
    };
}