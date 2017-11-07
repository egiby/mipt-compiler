%{
#include <iostream>
#include <cstdlib>

#include "ast/Scanner.h"
#undef YY_DECL
#define YY_DECL int Scanner::yylex(yy::parser::semantic_type* const lval, yy::parser::location_type *yylloc)

#define YY_USER_ACTION yylloc->step(); yylloc->columns(yyleng);

using std::cerr;
using token = yy::parser::token;
%} 

%option noyywrap
%option yylineno
%option c++

%option yyclass="Scanner"
%option nodefault

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
UNSIGNED_INTEGER ([1-9][0-9]*)|0
WHITE_SPACE [ \t]*
LINE_COMMENT "//".*\n
EOL (\n)|(\r\n)

%%
%{
	yylval = lval;
%}

{WHITE_SPACE} {
}
{EOL} {
	yylloc->lines();
}
{LINE_COMMENT} {
}

class {
	return token::T_CLASS;
}
public{WHITE_SPACE}static{WHITE_SPACE}void{WHITE_SPACE}main {
	return token::T_MAIN;
}
"System.out.println" {
	return token::T_PRINT;
}
"String[]" {
	return token::T_STRING_ARRAY;
}
public {
	return token::T_PUBLIC;
}
"return" {
	return token::T_RETURN;
}

if {
	return token::T_IF;
}
else {
	return token::T_ELSE;
}
while {
	return token::T_WHILE;
}

"int[]" {
	return token::T_INT_ARRAY;
}
extends {
	return token::T_EXTENDS;
}
int {
	return token::T_INT;
}
boolean {
	return token::T_BOOL;
}
true {
	return token::T_TRUE;
}
false {
	return token::T_FALSE;
}
this {
	return token::T_THIS;
}
new {
	return token::T_NEW;
}
length {
	return token::T_LENGTH;
}

"+" {
	return token::T_PLUS;
}
"-" {
	return token::T_MINUS;
}
"*" {
	return token::T_MULTIPLY;
}

"=" {
	return token::T_ASSIGN;
}

"&&" {
	return token::T_AND;
}
"||" {
	return token::T_OR;
}
"!" {
	return token::T_NOT;
}

"<" {
	return token::T_LESS;
}

"." {
	return token::T_DOT;
}
"," {
	return token::T_COMMA;
}

";" {
	return token::T_SEMICOLON;
}

"}" {
	return token::T_RBRACE;
}
"{" {
	return token::T_LBRACE;
}

")" {
	return token::T_RPAREN;
}
"(" {
	return token::T_LPAREN;
}

"]" {
	return token::T_RBRACKET;
}
"[" {
	return token::T_LBRACKET;
}

{UNSIGNED_INTEGER} {
	int value = std::atoi(yytext);
	yylval->build<int>(value);
	return token::T_INT_LITERAL;
}
{IDENTIFIER} {
	yylval->build<std::string>(yytext);
	return token::T_ID;
}
<<EOF>> {
	return token::T_EOF;
}
. {
	cerr << "Trash!!\n";
}
%%


/*int main() {
	Scanner lexer(&std::cin);
	lexer.yylex();
	return 0;
}*/