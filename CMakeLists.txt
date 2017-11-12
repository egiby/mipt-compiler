set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-deprecated-register")

cmake_minimum_required(VERSION 3.1)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

bison_target(parser
        ast/parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)

flex_target(lexer
        ast/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)

add_flex_bison_dependency(lexer parser)

set(SyntaxTreeSrc
        ast/tree/Program.cpp
        ast/tree/Class.cpp
        ast/tree/VarDeclaration.cpp
        ast/tree/MethodDeclaration.cpp
        ast/tree/Statement.cpp
        ast/tree/Expression.cpp
        )

set(Visitors
        ast/tree/visitors/PrettyPrinterVisitor.cpp
        ast/tree/visitors/PrinterDemo.cpp
        )

add_executable(parser
        ${SyntaxTreeSrc}
        ${Visitors}
        ast/tree/visitors/main.cpp
        ${FLEX_lexer_OUTPUTS}
        ${BISON_parser_OUTPUTS}
        )

include_directories(. ${CMAKE_CURRENT_BINARY_DIR})
