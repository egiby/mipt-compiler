#pragma once

#include "common.h"

#include "Exceptions.h"

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

    template<class Map>
    void CheckIdentifier(const Map& map, const IdentifierInfo& id) {
        if (map.find(id.GetId()) != map.end()) {
            throw RedefinitionException(id.GetLocation(), id.GetId(), map[id.GetId()].GetLocation());
        }
    }
}