#include "TreeBuilder.h"

#include <ast/Scanner.h>

#include <parser.tab.hh>

NSyntaxTree::Program NSyntaxTree::BuildTree(std::istream *input) {
    Scanner scanner(input);

    NSyntaxTree::Program program;
    yy::parser parser(scanner, program);
    parser.parse();

    return std::move(program);
}
