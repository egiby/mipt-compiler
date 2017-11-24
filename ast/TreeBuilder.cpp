#include "TreeBuilder.h"

#include <ast/Scanner.h>

#include <parser.tab.hh>

#include <memory>

NSyntaxTree::Program NSyntaxTree::BuildTree(std::istream *input) {
    std::shared_ptr<NUtil::StringInterner> interner(new NUtil::StringInterner());

    Scanner scanner(input, interner);

    NSyntaxTree::Program program;
    program.interner = interner;
    yy::parser parser(scanner, program);
    parser.parse();

    return std::move(program);
}
