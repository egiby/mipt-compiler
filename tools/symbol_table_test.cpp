#include <ast/TreeBuilder.h>

#include <symbol_table/SymbolTableCreatorVisitor.h>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "There must be one argument - minijava file for parsing" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);
    auto program = NSyntaxTree::BuildTree(&input);

    NSymbolTable::SymbolTable table;
    NSymbolTable::SymbolTableCreatorVisitor creator(table);
    creator.Visit(&program);

    std::cout << table.GetMainClassId()->String() << std::endl;
}