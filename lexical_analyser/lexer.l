%{
#include <cstdio>


int line_number = 0;
int column_number = 0;

static void printLocation()
{
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

	printf( "%s", yytext );
}

%} 

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
WHITE_SPACE [ \t\n]*

%%
class {
    printf("CLASS\n");
}
public{WHITE_SPACE}static{WHITE_SPACE}void{WHITE_SPACE}main {
    printf("MAIN\n");
}
"int[]" {
    printf("INT_ARRAY");
}
int {
    printf("INT");
}
boolean {
    printf("BOOL");
}
"{" {
    printf("{\n");
}
"}" {
    printf("}\n");
}
"(" {

}
")" {

}
"[" {

}
"]" {

}
%%
