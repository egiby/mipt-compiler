set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

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

add_executable(parser ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc
        ${BISON_parser_OUTPUTS})

include_directories(. ${CMAKE_CURRENT_BINARY_DIR})
