cmake_minimum_required(VERSION 3.2)

project(ast)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_compile_options(-Og -Wall -Wextra -Werror -std=c++20)

add_library(postfixAst
	Node.cpp
	Parser.cpp
)
