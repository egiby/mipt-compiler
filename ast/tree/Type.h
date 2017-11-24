#pragma once

#include <util/Symbol.h>

#include <string>

namespace NSyntaxTree {
    enum EType {
        INT,
        BOOL,
        INT_ARRAY,
        CLASS
    };
    
    struct Type {
        EType type = CLASS;
        //std::string id;
        const NUtil::Symbol* id;
    };
}