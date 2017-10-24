#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"

class Scanner : public yyFlexLexer {
public:
    Scanner(std::istream* in, std::ostream* out = 0) : yyFlexLexer(in, out) {}

    using FlexLexer::yylex;
    virtual int yylex(yy::parser::semantic_type* const lval);
private:
    yy::parser::semantic_type* yylval = nullptr;
};
