#include "NNForm.hpp"
#include "NNFPattern.hpp"

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

const detail::PatternRewriteMap& detail::getPatternRewriteMap()
{
	using namespace nnf::pattern;
	static const PatternRewriteMap map =
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
	for (const auto& [pattern, rewrite] : getPatternRewriteMap())
	{
		if (tree == pattern)
		{
			if (tree.value == '!')
				return generateTree(rewrite(tree));
			return rewrite(tree);
		}
	}
	return tree;
}

ast::tree& detail::generateTree(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	rewritePattern(tree);
	if (tree.size() >= 1)
		generateTree(tree.fst_child());
	if (tree.size() == 2)
		generateTree(tree.snd_child());
	return rewritePattern(tree);
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
