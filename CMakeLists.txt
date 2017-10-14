set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

cmake_minimum_required(VERSION 3.1)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(parser
        analysis/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/mc_parser.tab.cc)

FLEX_TARGET(lexer
        analysis/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc
        )

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_executable(lexer ${CMAKE_CURRENT_BINARY_DIR}/clion_lex.yy.cc)

