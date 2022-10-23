#include "NNForm.hpp"
#include <iostream>
#include <algorithm>

std::string negation_normal_form(const std::string& formula)
{
	return nnf::negation_normal_form(formula);
}

auto testNNF(const std::string& s, bool showTree = true)
{
	std::cout << "Transforming: " << s << '\n';

	auto mTree = ast::generateTree(s);
	if (!mTree)
	{
		std::cerr << "Invalid formula: " << s << '\n';
		return ast::tree(ast::placeholder);
	}

	auto copy = *mTree;
	auto nnfTree = nnf::detail::generateTree(copy);

	if (showTree)
	{
		std::cout << "Tree before:\n";
		printTree(*mTree);
		std::cout << "Tree after:\n";
		printTree(nnfTree);
	}

	auto str = negation_normal_form(s);
	std::cout << "Transformed string: " << str << '\n';

	if (std::ranges::none_of(s, [](char c) { return std::isalpha(c); }))
	{
		std::cout << std::boolalpha
				  << "Original  formula result: " << mTree->exec() << '\n'
				  << "Processed formula result: " << nnfTree.exec() << '\n';
	}
	return nnfTree;
}

int main()
{
	// testNNF("AB|C&!");
	// testNNF("AB|C=");
	// testNNF("AB|C>");
	// testNNF("AB&!");
	// testNNF("AB!|C&!");
	// testNNF("AB|C&D=X>"); // AB|C&D!&A!B!&C!|D&|X|
	testNNF("11|1&0=1>"); // AB|C&D!&A!B!&C!|D&|X|
	// testNNF("11|1&1=1>", true);
	// testNNF("ABOBA");
}
