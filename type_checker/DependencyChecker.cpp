#include "DependencyChecker.h"


namespace NTypeChecker {
    void CheckDependencies(const NSymbolTable::SymbolTable& symbolTable) {
        /*
         * Тут должны проверяться две вещи:
         * отсутствие циклических зависимостей и существование в глобальной области видимости классов,
         * упомянутых в extends.
         * Нарушение первого должно бросать CyclicDependencyException, второго - NonDeclaredSymbolException
         */
    }
}