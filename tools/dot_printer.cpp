#include <ast/TreeBuilder.h>
#include <ast/tree/visitors/PrettyPrinterVisitor.h>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "There must be one argument - minijava file for parsing" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);
    auto program = NSyntaxTree::BuildTree(&input);

    std::ofstream outPut("./graph.gv");

    NSyntaxTree::PrettyPrinterVisitor printer(outPut);
    std::cout << "Going to visit program" << std::endl;
    printer.Visit(&program);
    std::cout << "Program was visited" << std::endl;

    outPut.close();

    return 0;
}