cmake_minimum_required(VERSION 3.2)

project(ast)

set(CMAKE_CXX_STANDARD, 20)

add_compile_options(-O2 -Wall -Wextra -Werror -std=c++20)

add_executable(makeAst
	Node.cpp
	Parser.cpp
	test.cpp
)
