#include "ASTree.hpp"

void test(const std::string& formula)
{
	auto maybeRoot = Parser::generateTree(formula);
	if (!maybeRoot)
	{
		std::cerr << "Invalid formula: " << formula << '\n';
		return;
	}
	auto root = maybeRoot.value();
	printTree(root);
	std::cout << std::boolalpha << root.exec() << '\n';
}

int main()
{
	test("1!0|");
	test("1!0!|");
	test("1!0!0&|");
	test("10!^0&");
	test("1!!00!1!||&");
	test("1!!1^!");
	test("aboba");
	test("01||");
}
