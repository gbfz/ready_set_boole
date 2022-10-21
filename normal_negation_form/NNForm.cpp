#include "NNForm.hpp"

namespace nnf {

/* About generateTree and rewritePattern:
 *
 * If the node has one child - meaning its value is '!' -
 * I rewrite the node's child and then go back to handle rewritePattern on the current node.
 * The child's transformation can create a pattern with '!' at the start,
 * so to check that I call the rewriting procedure on the '!' node before going deeper into the tree.
 *
 * In case of a binary node the check is only done after handling the children nodes.
 */

const detail::PatternActionMap& detail::getPatternActionMap()
{
	using namespace nnf::pattern;
	static const PatternActionMap map =
	{
		{ implicationPattern(),		rewriteImplication		},
		{ equivalencePattern(),		rewriteEquivalence		},
		{ deMorgans1Pattern(),		rewriteDeMorgans1		},
		{ deMorgans2Pattern(),		rewriteDeMorgans2		},
		{ doubleNegationPattern(),	rewriteDoubleNegation	},
	};
	return map;
}

ast::tree& detail::rewritePattern(ast::tree& tree)
{
	for (auto const& [pattern, functor] : getPatternActionMap())
	{
		if (tree == pattern)
		{
			if (tree.value == '!')
				return generateTree(functor(tree));
			return functor(tree);
		}
	}
	return tree;
}

ast::tree& detail::generateTree(ast::tree& node)
{
	if (node.empty())
		return node;
	rewritePattern(node);
	switch (node.size())
	{
		case 1: rewritePattern(node.fst_child());
				break;
		case 2: generateTree(node.fst_child());
				generateTree(node.snd_child());
				break;
	}
	return rewritePattern(node);
}

std::string negation_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
	{
		std::cerr << "Invalid formula: " << s << '\n';
		return "";
	}
	auto nnfTree = nnf::detail::generateTree(*maybeTree);
	return ast::treeToString(nnfTree);
}

} // namespace nnf
