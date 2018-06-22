#include <ast/TreeBuilder.h>
#include <ast/tree/visitors/PrettyPrinterVisitor.h>

#include <symbol_table/SymbolTableBuilder.h>

#include <irt/translator/IRPrettyPrinter.h>
#include <irt/translator/X86IRBuilder.h>
#include <irt/translator/Canoniser.h>

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

    NSymbolTable::SymbolTable symbolTable = NSymbolTable::BuildSymbolTable(program);

    NIRTree::IRPrettyPrinter irPrinter(outIrt);
    NIRTree::IRForest forest = NIRTree::BuildTree(program, symbolTable);

    irPrinter.Visit(forest);

    outIrt.close();

    // linearized irt
    std::ofstream outLinearIrt("./graph_irt_canon.gv");
    NIRTree::IRLinearForest linearForest;
    NIRTree::IRPrettyPrinter linearIRPrinter(outLinearIrt);

    for (auto &tree: forest) {
        linearForest.insert({tree.first, NIRTree::Canoniser::Canonise(tree.second.release())});
    }

    linearIRPrinter.Visit(linearForest);

    return 0;
}