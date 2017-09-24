%{
#include <stdio.h>


int line_number = 0;
int column_number = 0;

struct Location {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} typedef Location;

static Location yylloc;

static void updateLocation() {
	// Начало токена
	yylloc.first_line = line_number;
	yylloc.first_column = column_number;

	// Новое смещение
	for( int i = 0; i < yyleng; i++ ) {
		if( yytext[i] == '\n' ) {
			line_number++;
			column_number = 1;
		} else {
			column_number++;
		}
	}

	// Конец токена
	yylloc.last_line = line_number;
	yylloc.last_column = column_number;
}

static void processToken(const char* token) {
	printf("%s\n", token);
	
	updateLocation();
	printf("start: %d %d\n", yylloc.first_line, yylloc.first_column);
	printf("end: %d %d\n", yylloc.last_line, yylloc.last_column);
} 

%} 

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
WHITE_SPACE [ \t]*
EOL \n

%%
class {
    processToken("CLASS");
}
public{WHITE_SPACE}static{WHITE_SPACE}void{WHITE_SPACE}main {
    processToken("MAIN");
}
"System.out.println" {
	processToken("PRINT");
}
"String[]" {
	processToken("STRING_ARRAY");
}
if {
	processToken("IF");
}
else {
	processToken("ELSE");
}
while {
	processToken("WHILE");
}
"int[]" {
    processToken("INT_ARRAY");
}
extends {
	processToken("EXTENDS");
}
int {
    processToken("INT");
}
boolean {
    processToken("BOOL");
}
"+" {
	processToken("PLUS");
}
"*" {
	processToken("MULTIPLY");
}
"-" {
	processToken("MINUS");
}
"." {
	processToken("DOT");
}
"," {
	processToken("COMMA");
}
";" {
	processToken(";");
}
"{" {
    processToken("{");
}
"}" {
    processToken("}");
}
"(" {
	processToken("(");
}
")" {
	processToken(")");
}
"[" {
	processToken("[");
}
"]" {
	processToken("]");
}
{IDENTIFIER} {
	processToken("IDENTIFIER");
}
{WHITE_SPACE} {
	updateLocation();
}
{EOL} {
	updateLocation();
}
. {
	updateLocation();
	printf("Trash\t\t: %s\n", yytext);
}
%%
