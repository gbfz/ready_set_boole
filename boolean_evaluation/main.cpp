#include "ast.hpp"
#include <iostream>
#include <cassert>
#include <optional>

auto eval_formula(const std::string& formula) -> bool
{
	try {
		return Ast().build(formula).print().exec();
		// return Ast().build(formula).exec();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
}

auto print(bool b)
{
	std::cout << std::boolalpha << b << '\n';
}

auto test(const std::string& s, std::optional<bool> expected)
{
	auto b = eval_formula(s);
	print(b);
	if (expected) assert(b == expected);
}

auto main() -> int
{
	// test("1", true);
	// test("101&&", false);
	test("11|11||", true);
	// test("10>", false);
	// test("011>|", true);
	// test("101|&", true);
	// test("|", {});
	// test("11", {});
}
