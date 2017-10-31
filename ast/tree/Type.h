#pragma once

#include <string>

namespace NSyntaxTree {
    struct Type {
        enum EType {
            INT,
            BOOL,
            INT_ARRAY,
            CLASS
        };

        std::string id;
    };
}