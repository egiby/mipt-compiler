#include "PrettyPrinterVisitor.h"

#include <ast/Scanner.h>

#include <parser.tab.hh>

#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    return 0;
    if (argc == 2) {
        std::cerr << "Hey, babe, this is main!" << std::endl;
        return 0;
    }
    if (argc <= 1) {
        std::cerr << "There must be one argument - minijava file for parsing" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);

    std::cout << "Going to create scanner" << std::endl;
    Scanner scanner(&input);
    std::cout << "Scanner was created" << std::endl;

    NSyntaxTree::Program program;
    yy::parser parser(scanner, program);
    parser.parse();

    std::ofstream outPut("./graph.gv");

    NSyntaxTree::PrettyPrinterVisitor printer(outPut);
    std::cout << "Goint to visit program" << std::endl;
    printer.Visit(&program);
    std::cout << "Program was visited" << std::endl;

    outPut.close();

    return 0;
}