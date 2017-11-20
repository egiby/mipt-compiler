#pragma once

#include "common.h"


namespace NSymbolTable {
    class IdentifierInfo {
    protected:
        const Symbol* id = nullptr;
        Location location;
    public:
        inline IdentifierInfo(const Symbol* _id, const NSyntaxTree::Location& _location)
            : id(_id), location(_location) {
        }

        inline const Symbol* GetId() const {
            return id;
        }

        inline const NSyntaxTree::Location& GetLocation() const {
            return location;
        }
    };
}