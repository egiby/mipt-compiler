%skeleton "lalr1.cc"

%{

%}

%debug
%defines


%token T_CLASS
%token T_MAIN
%token T_PRINT
%token T_STRING_ARRAY

%token T_IF
%token T_ELSE
%token T_WHILE

%token T_INT_ARRAY
%token T_INT
%token T_BOOL
%token T_TRUE
%token T_FALSE

%token T_EXTENDS
%token T_THIS
%token T_NEW

%token T_PLUS
%token T_MINUS
%token T_MULTIPLY

%token T_ASSIGN

%token T_AND
%token T_OR
%token T_NOT

%token T_LESS

%token T_DOT
%token T_COMMA

%token T_SEMICOLON

%token T_RBRACE
%token T_LBRACE

%token T_RPAREN
%token T_LPAREN

%token T_RBRACKET
%token T_LBRACKET

%token T_ID
%token <int> T_INT_LITERAL

%%
start :
;
%%

int main(void) {
    yyparse();
}