%skeleton "lalr1.cc"

%{
    #include "tree/NodeTypes.h"
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

%type<std::unique_ptr<NSyntaxTree::MainClass>> MainClass
%type<std::vector<std::unique_ptr<NSyntaxTree::ClassDeclaration>>> ClassDeclarations
%type<std::unique_ptr<NSyntaxTree::ClassDeclaration>> ClassDeclaration

%type<std::vector<std::unique_ptr<NSyntaxTree::VarDeclaration>>> VarDeclarations
%type<std::unique_ptr<NSyntaxTree::VarDeclaration>> VarDeclaration

%type<NSyntaxTree::Type> Type

%type<std::vector<std::unique_ptr<NSyntaxTree::MethodDeclaration>>> MethodDeclarations
%type<std::unique_ptr<NSyntaxTree::MethodDeclaration>> MethodDeclaration

%type<std::vector<std::unique_ptr<NSyntaxTree::IStatement>>> Statements
%type<std::unique_ptr<NSyntaxTree::IStatement>> Statement

%type<std::unique_ptr<NSyntaxTree::IExpression>> Expression
%type<std::vector<std::unique_ptr<NSyntaxTree::IExpression>>> ArgumentExpressions

%type<std::vector<std::pair<NSyntaxTree::Type, std::string>>> MethodArguments
%type<std::pair<NSyntaxTree::Type, std::string>> MethodArgument

%%
Goal 
    : MainClass ClassDeclarations {
        program.mainClass = std::move($1);
        program.classes = std::move($2);
    }
;
MainClass
    : T_CLASS T_ID[name] T_LBRACE
        T_MAIN T_LPAREN T_STRING_ARRAY T_ID[args] T_RPAREN T_LBRACE
            Statement
        T_RBRACE
    T_RBRACE {
        $$ = std::make_unique<NSyntaxTree::MainClass>($name, $args, std::move($Statement));
    }
;
ClassDeclarations
    : %empty {}
    | ClassDeclarations ClassDeclaration {
        $$ = std::move($1);
        $$.push_back(std::move($2));
    }
;
ClassDeclaration
    : T_CLASS T_ID[name] T_LBRACE
        VarDeclarations
        MethodDeclarations
    T_RBRACE {
        $$ = std::make_unique<NSyntaxTree::ClassDeclaration>($name, std::string(), std::move($VarDeclarations), std::move($MethodDeclarations));
    }
    | T_CLASS T_ID[name] T_EXTENDS T_ID[parent] T_LBRACE
        VarDeclarations
        MethodDeclarations
    T_RBRACE {
        $$ = std::make_unique<NSyntaxTree::ClassDeclaration>($name, $parent, std::move($VarDeclarations), std::move($MethodDeclarations));
    }
;
VarDeclarations
    : %empty {}
    | VarDeclarations VarDeclaration {
        $$ = std::move($1);
        $$.push_back(std::move($2));
    }
;
VarDeclaration
    : Type T_ID T_SEMICOLON {
        $$ = std::make_unique<NSyntaxTree::VarDeclaration>($1, $2);
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
    : %empty {}
    | MethodDeclarations MethodDeclaration {
        $$ = std::move($1);
        $$.push_back(std::move($2));
    }
;
MethodDeclaration
    : T_PUBLIC Type[type] T_ID[name] T_LPAREN MethodArguments T_RPAREN T_LBRACE
        VarDeclarations
        Statements
        T_RETURN Expression T_SEMICOLON
    T_RBRACE {
        $$ = std::make_unique<NSyntaxTree::MethodDeclaration>($type, $name, $MethodArguments, $VarDeclarations, $Statements, $Expression);
    }
;
Statements
    : %empty {}
    | Statements Statement {
        $$ = std::move($1);
        $$.push_back(std::move($2));
    }
;
Statement
    : T_LBRACE
        Statements
    T_RBRACE {
        $$.reset(new NSyntaxTree::Statements(std::move($Statements)));
    }
    | T_IF T_LPAREN Expression T_RPAREN Statement[trueStatement] T_ELSE Statement[falseStatement] {
        $$.reset(new NSyntaxTree::IfStatement($Expression, $trueStatement, $falseStatement));
    }
    | T_WHILE T_LPAREN Expression T_RPAREN Statement[statement] {
        $$.reset(new NSyntaxTree::WhileStatement($Expression, $statement));
    }
    | T_PRINT T_LPAREN Expression T_RPAREN T_SEMICOLON {
        $$.reset(new NSyntaxTree::PrintlnStatement($Expression));
    }
    | T_ID T_ASSIGN Expression T_SEMICOLON {
        $$.reset(new NSyntaxTree::AssignStatement($1, std::move($3)));
    }
    | T_ID T_LBRACKET Expression[index] T_RBRACKET T_ASSIGN Expression[rvalue] T_SEMICOLON {
        $$.reset(new NSyntaxTree::AssignStatement($1, std::move($index), std::move($rvalue)));
    }
;
Expression
    : Expression[left] T_AND Expression[right] {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::AND, $left, $right));
    }
    | Expression[left] T_LESS Expression[right] {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::LESS, $left, $right));
    }
    | Expression[left] T_PLUS Expression[right] {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::PLUS, $left, $right));
    }
    | Expression[left] T_MINUS Expression[right] {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::MINUS, $left, $right));
    } 
    | Expression[left] T_MULTIPLY Expression[right] {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::EBinaryExprType::MULTIPLY, $left, $right));
    }
    | Expression[array] T_RBRACKET Expression[index] T_LBRACKET {
        $$.reset(new NSyntaxTree::BinaryExpression(NSyntaxTree::ArrayElementAccessExpression(std::move($array), std::move($index))));
    }
    | Expression[array] T_DOT T_LENGTH {
        $$.reset(new NSyntaxTree::ArrayLengthExpression(std::move($1)));
    }
    | Expression[object] T_DOT T_ID[methodName] T_LPAREN ArgumentExpressions[args] T_RPAREN {
        $$.reset(new NSyntaxTree::MethodCallExpression(std::move($object), $methodName, std::move($args)));
    }
    | T_INT_LITERAL {
        $$.reset(new NSyntaxTree::IntegerLiteralExpression($1));
    }
    | T_TRUE {
        $$.reset(new NSyntaxTree::BoolLiteralExpression(true));
    }
    | T_FALSE {
        $$.reset(new NSyntaxTree::BoolLiteralExpression(false));
    }
    | T_ID {
        $$.reset(new NSyntaxTree::IdentifierExpression($1));
    }
    | T_THIS {
        $$.reset(new NSyntaxTree::ThisExpression());
    }
    | T_NEW T_INT T_LBRACKET Expression[size] T_RBRACKET {
        $$.reset(new NSyntaxTree::NewIntArrayExpression($size));
    }
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