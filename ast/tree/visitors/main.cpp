#include <iostream>
#include <fstream>
#include "PrettyPrinterVisitor.h"
#include "DemoTreeCreator.h"
#include "ast/tree/Program.h"

int main() {
    std::ofstream outPut;
    outPut.open("./graph.gv");
    
    NSyntaxTree::Program program;
    NSyntaxTree::CreateDemoTree(program);
    NSyntaxTree::PrettyPrinterVisitor printer(outPut);

    printer.Visit(&program);

    outPut.close();

    return 0;
}