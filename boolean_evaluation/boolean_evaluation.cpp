#include "ASTree.hpp"

bool eval_formula(const std::string& formula)
{
	std::optional<ast::tree> maybeTree = ast::generateTree(formula);
	if (!maybeTree)
	{
		std::cerr << "Invalid formula: " << formula << '\n';
		return {};
	}
	return maybeTree->exec();
}
