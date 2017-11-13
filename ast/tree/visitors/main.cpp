#include "PrettyPrinterVisitor.h"

#include <ast/Scanner.h>

#include <parser.tab.hh>

#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "There must be one argument - minijava file for parsing" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);
    Scanner scanner(&input);

    NSyntaxTree::Program program;
    yy::parser parser(scanner, program);
    parser.parse();

    std::ofstream outPut("./graph.gv");

    NSyntaxTree::PrettyPrinterVisitor printer(outPut);
    printer.Visit(&program);

    outPut.close();

    return 0;
}