#include "ast.hpp"
#include <iostream>

auto main() -> int
{
	std::cout << std::boolalpha;
	Ast ast;
	// ast.build("101|&"); // true
	// ast.build("101&&"); // false
	// ast.build("10>"); // true
	ast.build("011>|");
	ast.print();
	std::cout <<  ast.exec() << std::endl;
}
