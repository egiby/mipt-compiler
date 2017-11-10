%skeleton "lalr1.cc"

%{
    #include <iostream>
    using std::cerr;
    using std::endl;
%}

%debug
%defines
%require "3.0"

%locations

%define api.value.type variant

%code requires {
    #include "ast/tree/NodeTypes.h"
    class Scanner;
}

%parse-param { Scanner &scanner }
%parse-param { NSyntaxTree::Program& program }

%code {
    #include "ast/Scanner.h"

    #undef yylex
    #define yylex scanner.yylex
}

%token T_CLASS
%token T_MAIN
%token T_PRINT
%token T_STRING_ARRAY
%token T_PUBLIC
%token T_RETURN

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
%token T_LENGTH

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

%token <std::string> T_ID
%token <int> T_INT_LITERAL

%token T_EOF

%type<NSyntaxTree::MainClass*> MainClass;
%type<std::vector<std::unique_ptr<NSyntaxTree::ClassDeclaration>>*> ClassDeclarations;
%type<NSyntaxTree::ClassDeclaration*> ClassDeclaration;

%type<std::vector<std::unique_ptr<NSyntaxTree::VarDeclaration>>*> VarDeclarations;
%type<NSyntaxTree::VarDeclaration*> VarDeclaration;

%type<NSyntaxTree::Type> Type;

%type<std::vector<std::unique_ptr<NSyntaxTree::MethodDeclaration>>*> MethodDeclarations;
%type<NSyntaxTree::MethodDeclaration*> MethodDeclaration;
%type<std::vector<std::pair<NSyntaxTree::Type, std::string>>> MethodArguments NotEmptyArgumentList;


%type<std::vector<std::unique_ptr<NSyntaxTree::IStatement>>*> Statements;
%type<NSyntaxTree::IStatement*> Statement;

%type<NSyntaxTree::IExpression*> Expression;
%type<std::vector<std::unique_ptr<NSyntaxTree::IExpression>>*> ArgumentExpressions NotEmptyArgumentExpressions;

%%
Goal 
    : MainClass ClassDeclarations {
        program.mainClass.reset($1);
        program.classes.reset($2);
    }
;
MainClass
    : T_CLASS T_ID[name] T_LBRACE
        T_MAIN T_LPAREN T_STRING_ARRAY T_ID[args] T_RPAREN T_LBRACE
            Statement
        T_RBRACE
    T_RBRACE {
        $$ = new NSyntaxTree::MainClass($name, $args, $Statement);
    }
;
ClassDeclarations
    : %empty {
        $$ = new std::vector<std::unique_ptr<NSyntaxTree::ClassDeclaration>>();
    }
    | ClassDeclarations ClassDeclaration {
        $$ = $1;
        $$->emplace_back($2);
    }
;
ClassDeclaration
    : T_CLASS T_ID[name] T_LBRACE
        VarDeclarations
        MethodDeclarations
    T_RBRACE {
        $$ = new NSyntaxTree::ClassDeclaration($name, std::string(), $VarDeclarations, $MethodDeclarations);
    }
    | T_CLASS T_ID[name] T_EXTENDS T_ID[parent] T_LBRACE
        VarDeclarations
        MethodDeclarations
    T_RBRACE {
        $$ = new NSyntaxTree::ClassDeclaration($name, $parent, $VarDeclarations, $MethodDeclarations);
    }
;
VarDeclarations
    : %empty {
        $$ = new std::vector<std::unique_ptr<NSyntaxTree::VarDeclaration>>();
    }
    | VarDeclarations VarDeclaration {
        $$ = $1;
        $$->emplace_back($2);
    }
;
VarDeclaration
    : Type T_ID T_SEMICOLON {
        $$ = new NSyntaxTree::VarDeclaration($1, $2);
    }
;
Type
    : T_INT {
        $$ = NSyntaxTree::Type{NSyntaxTree::EType::INT, std::string()};
    }
    | T_INT_ARRAY {
        $$ = NSyntaxTree::Type{NSyntaxTree::EType::INT_ARRAY, std::string()};
    }
    | T_BOOL {
        $$ = NSyntaxTree::Type{NSyntaxTree::EType::BOOL, std::string()};
    }
    | T_ID {
        $$ = NSyntaxTree::Type{NSyntaxTree::EType::CLASS, $1};
    }
;
MethodDeclarations
    : %empty {
        $$ = new std::vector<std::unique_ptr<NSyntaxTree::MethodDeclaration>>();
    }
    | MethodDeclarations MethodDeclaration {
        $$ = $1;
        $$->emplace_back($2);
    }
;
MethodDeclaration
    : T_PUBLIC Type[type] T_ID[name] T_LPAREN MethodArguments T_RPAREN T_LBRACE
        VarDeclarations
        Statements
        T_RETURN Expression T_SEMICOLON
    T_RBRACE {
        $$ = new NSyntaxTree::MethodDeclaration($type, $name, $MethodArguments, $VarDeclarations, $Statements, $Expression);
    }
;
NotEmptyArgumentList
    : Type T_ID {
        $$.push_back({$1, $2});
    }
    | NotEmptyArgumentList T_COMMA Type T_ID {
        $$ = std::move($1);
        $$.push_back({$3, $4});
    }
;
MethodArguments
    : %empty {}
    | NotEmptyArgumentList {
        $$ = std::move($1);
    }
;
Statements
    : %empty {
        $$ = new std::vector<std::unique_ptr<NSyntaxTree::IStatement>>();
    }
    | Statements Statement {
        $$ = $1;
        $$->emplace_back($2);
    }
;
Statement
    : T_LBRACE
        Statements
    T_RBRACE {
        $$ = new NSyntaxTree::Statements($Statements);
    }
    | T_IF T_LPAREN Expression T_RPAREN Statement[trueStatement] T_ELSE Statement[falseStatement] {
        $$ = new NSyntaxTree::IfStatement($Expression, $trueStatement, $falseStatement);
    }
    | T_WHILE T_LPAREN Expression T_RPAREN Statement[statement] {
        $$ = new NSyntaxTree::WhileStatement($Expression, $statement);
    }
    | T_PRINT T_LPAREN Expression T_RPAREN T_SEMICOLON {
        $$ = new NSyntaxTree::PrintlnStatement($Expression);
    }
    | T_ID T_ASSIGN Expression T_SEMICOLON {
        $$ = new NSyntaxTree::AssignStatement($1, $3);
    }
    | T_ID T_LBRACKET Expression[index] T_RBRACKET T_ASSIGN Expression[rvalue] T_SEMICOLON {
        $$ = new NSyntaxTree::ArrayElementAssignmentStatement($1, $index, $rvalue);
    }
;
Expression
    : Expression[left] T_AND Expression[right] {
        $$ = new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::AND, $left, $right);
    }
    | Expression[left] T_LESS Expression[right] {
        $$ = new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::LESS, $left, $right);
    }
    | Expression[left] T_PLUS Expression[right] {
        $$ = new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::PLUS, $left, $right);
    }
    | Expression[left] T_MINUS Expression[right] {
        $$ = new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::MINUS, $left, $right);
    } 
    | Expression[left] T_MULTIPLY Expression[right] {
        $$ = new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::MULTIPLY, $left, $right);
    }
    | Expression[array] T_RBRACKET Expression[index] T_LBRACKET {
        $$ = new NSyntaxTree::ArrayElementAccessExpression($array, $index);
    }
    | Expression[array] T_DOT T_LENGTH {
        $$ = new NSyntaxTree::ArrayLengthExpression($1);
    }
    | Expression[object] T_DOT T_ID[methodName] T_LPAREN ArgumentExpressions[args] T_RPAREN {
        $$ = new NSyntaxTree::MethodCallExpression($object, $methodName, $args);
    }
    | T_INT_LITERAL {
        $$ = new NSyntaxTree::IntegerLiteralExpression($1);
    }
    | T_TRUE {
        $$ = new NSyntaxTree::BoolLiteralExpression(true);
    }
    | T_FALSE {
        $$ = new NSyntaxTree::BoolLiteralExpression(false);
    }
    | T_ID {
        $$ = new NSyntaxTree::IdentifierExpression($1);
    }
    | T_THIS {
        $$ = new NSyntaxTree::ThisExpression();
    }
    | T_NEW T_INT T_LBRACKET Expression[size] T_RBRACKET {
        $$ = new NSyntaxTree::NewIntArrayExpression($size);
    }
    | T_NEW T_ID[clazz] T_LPAREN T_RPAREN {
        $$ = new NSyntaxTree::NewExpression($clazz);
    }
    | T_NOT Expression[expression] {
        $$ = new NSyntaxTree::NegateExpression($expression);
    }
    | T_LPAREN Expression[expression] T_RPAREN {
        $$ = $expression;
    }
;
NotEmptyArgumentExpressions
    : Expression {
        $$->emplace_back($1);
    }
    | ArgumentExpressions T_COMMA Expression {
        $$ = $1;
        $$->emplace_back($3);
    }
;
ArgumentExpressions
    : %empty {
        $$ = new std::vector<std::unique_ptr<NSyntaxTree::IExpression>>();
    }
    | NotEmptyArgumentExpressions {
        $$ = $1;
    }
;
%%

void yy::parser::error(const yy::parser::location_type& l, const std::string &err_message) {
    cerr << l << ": " << err_message << endl;
}

int main() {
    Scanner scanner(&std::cin);
    NSyntaxTree::Program program;
    yy::parser parser(scanner, program);
    parser.parse();
}