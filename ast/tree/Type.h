#pragma once

#include <string>

namespace NSyntaxTree {
    enum EType {
        INT,
        BOOL,
        INT_ARRAY,
        CLASS
    };
    
    struct Type {
        EType type;
        std::string id;
    };
}