set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

cmake_minimum_required(VERSION 3.1)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

#bison_target(parser
#        analysis/parser.y
#        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)

flex_target(lexer
        analysis/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)

#add_flex_bison_dependency(lexer parser)

add_executable(lexer ${FLEX_lexer_OUTPUTS})
