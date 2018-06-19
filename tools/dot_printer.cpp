#include <ast/TreeBuilder.h>
#include <ast/tree/visitors/PrettyPrinterVisitor.h>

#include <irt/translator/IRPrettyPrinter.h>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "There must be one argument - minijava file for parsing" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1]);

    // ast
    auto program = NSyntaxTree::BuildTree(&input);

    std::ofstream outPut("./graph_ast.gv");

    NSyntaxTree::PrettyPrinterVisitor printer(outPut);
    printer.Visit(&program);

    outPut.close();

    // irt
    std::ofstream outIrt("./graph_irt.gv");

    NIRTree::IRPrettyPrinter irPrinter(outIrt);

    auto globalRoot = NIRTree::GlobalIRTParent();

    irPrinter.Visit(&globalRoot);

    outIrt.close();

    return 0;
}