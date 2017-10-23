%option noyywrap
%option c++
%option yylineno

%{
#include "parser.tab.h"

#include <cstdio>
#include <exception>


class UnexpectedSymbolException: public std::exception {
public:
    const char* what() const noexcept {
        return "Bad symbol";
    }
};


static int line_number = 0;
static int column_number = 0;

struct Location {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
};

static Location yylloc;

void updateLocation(const yyFlexLexer* lexer) {
	// Начало токена
	yylloc.first_line = line_number;
	yylloc.first_column = column_number;

	// Новое смещение
	auto yyleng = lexer->YYLeng();
	auto yytext = lexer->YYText();
	for( int i = 0; i < yyleng; i++ ) {
		if( yytext[i] == '\n' ) {
			line_number++;
			column_number = 0;
		} else {
			column_number++;
		}
	}

	// Конец токена
	yylloc.last_line = line_number;
	yylloc.last_column = column_number;
}

void processToken(const yyFlexLexer* lexer, const char* tokenName) {
	printf("%s\n", tokenName);
	
	updateLocation(lexer);
	printf("start: %d %d\n", yylloc.first_line, yylloc.first_column);
	printf("end: %d %d\n", yylloc.last_line, yylloc.last_column);
}

%} 

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
UNSIGNED_INTEGER ([1-9][0-9]*)|0
WHITE_SPACE [ \t]*
LINE_COMMENT "//".*\n
EOL \n

%%
{WHITE_SPACE} {
	updateLocation(this);
}
{EOL} {
	updateLocation(this);
}
{LINE_COMMENT} {
	processToken(this, "LINE_COMMENT");
}

class {
    processToken(this, "CLASS");
}
public{WHITE_SPACE}static{WHITE_SPACE}void{WHITE_SPACE}main {
    processToken(this, "MAIN");
}
"System.out.println" {
	processToken(this, "PRINT");
}
"String[]" {
	processToken(this, "STRING_ARRAY");
}

if {
	processToken(this, "IF");
}
else {
	processToken(this, "ELSE");
}
while {
	processToken(this, "WHILE");
}

"int[]" {
    processToken(this, "INT_ARRAY");
}
extends {
	processToken(this, "EXTENDS");
}
int {
    processToken(this, "INT");
}
boolean {
    processToken(this, "BOOL");
}
true {
	processToken(this, "TRUE");
}
false {
	processToken(this, "FALSE");
}
this {
	processToken(this, "THIS");
}
new {
	processToken(this, "NEW");
}

"+" {
	processToken(this, "PLUS");
}
"*" {
	processToken(this, "MULTIPLY");
}
"-" {
	processToken(this, "MINUS");
}

"=" {
	processToken(this, "EQUAL");
}

"&&" {
	processToken(this, "AND");
}
"||" {
	processToken(this, "OR");
}
"!" {
	processToken(this, "NEGATION");
}

"<" {
	processToken(this, "LESS");
}

"." {
	processToken(this, "DOT");
}
"," {
	processToken(this, "COMMA");
}

";" {
	processToken(this, ";");
}

"{" {
    processToken(this, "{");
}
"}" {
    processToken(this, "}");
}

"(" {
	processToken(this, "(");
}
")" {
	processToken(this, ")");
}

"[" {
	processToken(this, "[");
}
"]" {
	processToken(this, "]");
}

{UNSIGNED_INTEGER} {
	processToken(this, "UNSIGNED_INTEGER");
}
{IDENTIFIER} {
	processToken(this, "IDENTIFIER");
}
. {
	updateLocation(this);
	printf("Trash!!!!!!!!!!!!!!!!!!!!!!!!!!!: %s\n", yytext);
	throw UnexpectedSymbolException();
}
%%


int main() {
	yyFlexLexer lexer;
	lexer.yylex();
	return 0;
}