#include "ASTree.hpp"
#include "Pattern.hpp"
#include <unordered_map>

struct hashTree
{
	size_t operator()(const ast::tree& node) const
	{
		auto hasher = std::hash<size_t>();
		auto fst = hasher(node.value) + hasher(node.size());
		switch (node.size())
		{
			case 0: return fst;
			case 1: return fst + hasher(node.fst_child().value) + hasher(node.fst_child().size());
			case 2: return fst 
						 + hasher(node.fst_child().value) + hasher(node.fst_child().size())
						 + hasher(node.snd_child().value) + hasher(node.snd_child().size());
		}
		return std::string::npos;
	}
};

enum class Pattern
{
	DNeg,
	Impl,
	Eq,
	dM1,
	dM2,
	None
};

ast::tree& negation_normal_form(ast::tree& tree);

/*
Pattern matchPattern(const ast::tree& tree)
{
	using namespace pattern;
	static const std::unordered_map<ast::tree, Pattern, hashTree> patternMap =
	{
		{ doubleNegationPattern(),	Pattern::DNeg },
		{ implicationPattern(),		Pattern::Impl },
		{ equivalencePattern(),		Pattern::Eq },
		{ deMorgans1Pattern(),		Pattern::dM1 },
		{ deMorgans2Pattern(),		Pattern::dM2 },
	};
	for (const auto& [pTree, pEnum] : patternMap)
		if (tree == pTree)
			return pEnum;
	return Pattern::None;
}

ast::tree& rewrite(ast::tree& tree, Pattern pattern)
{
	using namespace pattern;
	using modifierT = decltype(&rewriteDoubleNegation);
	static const std::unordered_map<Pattern, modifierT> rewriteMap =
	{
		{ Pattern::DNeg,	rewriteDoubleNegation },
		{ Pattern::Impl,	rewriteImplication },
		{ Pattern::Eq,		rewriteEquivalence },
		{ Pattern::dM1, 	rewriteDeMorgans1 },
		{ Pattern::dM2, 	rewriteDeMorgans2 },
		{ Pattern::None,	[](ast::tree& t) -> ast::tree& { return t; } }
	};
	return rewriteMap.at(pattern)(tree);
}


ast::tree& negation_normal_form(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	/// std::cout << "\n-----\n";
	/// printTree(tree);
	/// std::cout << "-----\n";
	switch (tree.size())
	{
		case 2: 
			auto fstP = matchPattern(tree.fst_child());
			auto sndP = matchPattern(tree.snd_child());
		case 1: 
	}
	return tree;
}
*/

ast::tree& rewrite(ast::tree& tree, bool recall = false)
{
	using namespace pattern;
	using modifierT = decltype(&rewriteDoubleNegation);
	static const std::unordered_map<ast::tree, modifierT, hashTree> patternMap =
	{
		{ doubleNegationPattern(),	rewriteDoubleNegation },
		{ implicationPattern(),		rewriteImplication },
		{ equivalencePattern(),		rewriteEquivalence },
		{ deMorgans1Pattern(),		rewriteDeMorgans1 },
		{ deMorgans2Pattern(),		rewriteDeMorgans2 },

		// { distributivity1_in(),		rewriteDistr1_in },
		// { distributivity1_out(),	rewriteDistr1_out },
		// { distributivity2_in(),		rewriteDistr2_in },
		// { distributivity2_out(),	rewriteDistr2_out },

	};
	for (const auto& [pattern, functor] : patternMap)
		if (tree == pattern)
		{
			// printTree(tree);
			// return negation_normal_form(functor(tree));
			if (recall)
				return negation_normal_form(functor(tree));
			return functor(tree);
		}
	return tree;
}

ast::tree& negation_normal_form(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	switch (tree.size())

	{
		case 2: rewrite(tree.fst_child(), false);
				rewrite(tree.snd_child(), false);
				tree = rewrite(tree, true);
				negation_normal_form(tree.fst_child());
				negation_normal_form(tree.snd_child());
				break;
		case 1: rewrite(tree.fst_child(), false);
				tree = rewrite(tree, true);
				negation_normal_form(tree.fst_child());
				break;
	}
	/*
	tree = rewrite(tree);
	// std::cout << "\n-----\n";
	// printTree(tree);
	// std::cout << "-----\n";
	switch (tree.size())
	{
		case 1: negation_normal_form(tree.fst_child());
				tree = rewrite(tree);
				break;
		case 2: negation_normal_form(tree.fst_child());
				negation_normal_form(tree.snd_child());
				tree = rewrite(tree);
				break;
	}
	return tree;
	*/
	return tree;
}

std::string negation_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
	{
		std::cerr << "\nInvalid formula \"" << s << "\"\n";
		return s;
	}
	std::cout << "\nProcessing " << s << '\n';
	std::cout << "Before:\n";
	printTree(*maybeTree);
	auto nnfTree = negation_normal_form(*maybeTree);
	std::cout << "After:\n";
	printTree(nnfTree);
	return ast::treeToString(nnfTree);
}

void testNNF(const std::string& s)
{
	auto n = negation_normal_form(s);
	std::cout << "Transformed:\n";
	std::cout << n << '\n';
	std::cout << std::boolalpha << ast::generateTree(n).value().exec() << '\n';
}

int main()
{
	// test2();
	// testREq();
	// testRecog();
	// testDeM1();
	// testNNF();
	// testNNF("AB|C&!");
	// testNNF("AB|C=");
	// testNNF("AB|C>");
	// testNNF("AB&!");
	// testNNF("AB!|C&!");
	testNNF("AB|C&D=X>");
	// testNNF("11|0&1=1>");
	// should ideally yield ((1 ⋅(1 + 1)) ↔ 1) → 0 :: 11|1&1=0>

	// * Distributivity I:	AB|C&	≡	CA&CB&|
	// testNNF("AB|C&");
	// testNNF("CA&CB&|");

	// * Distributivity II:	AB&C|	≡	CA|CB|&
}

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	AB&A!B!&|
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 * Distributivity I:	AB|C&	≡	CA&CB&|
 * Distributivity II:	AB&C|	≡	CA|CB|&
 */

/* CA&CB&|D!&A!B!&C!|D&|X|
 */
