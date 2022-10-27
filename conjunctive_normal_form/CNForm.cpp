#include "CNForm.hpp"

namespace cnf {

const detail::PatternRewriteMap& detail::getPatternRewriteMap()
{
	using namespace cnf::pattern;
	static const PatternRewriteMap map =
	{
		{ docPatternL(),				rewriteDocL },
		{ docPatternR(),				rewriteDocR },
		{ doubleConjunctionPattern(),	rewriteDoubleConjunction },
		{ doubleDisjunctionPattern(),	rewriteDoubleDisjunction },
	};
	return map;
}

ast::tree& detail::rewritePattern(ast::tree& tree)
{
	for (const auto& [pattern, rewrite] : getPatternRewriteMap())
	{
		if (tree == pattern)
			return generateTree(rewrite(tree));
	}
	return tree;
}

ast::tree& detail::generateTree(ast::tree& node)
{
	if (node.empty())
		return node;
	rewritePattern(node);
	if (node.size() >= 1)
		generateTree(node.fst_child());
	if (node.size() == 2)
		generateTree(node.snd_child());
	return node;
}

std::string conjunctive_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
	{
		std::cerr << "Invalid formula: " << s << '\n';
		return "";
	}
	auto nnfTree = nnf::detail::generateTree(*maybeTree);
	auto cnfTree = cnf::detail::generateTree(nnfTree);
	return ast::treeToString(cnfTree);
}

}
