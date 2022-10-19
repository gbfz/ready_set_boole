// #include "ASTree.hpp"
#include "Pattern.hpp"
#include <unordered_map>

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

struct hashTree
{
	size_t operator()(const ast::tree& node) const
	{
		switch (node.size())
		{
			case 0: return (std::hash<int>()(node.value) % 3) << 1;
			case 1: return ((std::hash<int>()(node.value) % 3) << 1)
						 ^ (std::hash<int>()(node.fst_child().value) % 3 << 1);
			case 2: return ((std::hash<int>()(node.value) % 3) << 1)
						 ^ (std::hash<int>()(node.fst_child().value) % 3 << 1)
						 ^ (std::hash<int>()(node.snd_child().value) % 3 << 1);
		}
		return std::string::npos;
	}
};

ast::tree& rewrite(ast::tree& tree)
{
	using namespace pattern;
	using modifierT = decltype(&rewriteDoubleNegation);
	static const std::unordered_map<ast::tree, modifierT, hashTree> patternMap =
	{
		{ distributivity1_in(),		rewriteDistributivity1_in },
		{ distributivity1_out(),	rewriteDistributivity1_out },
		{ distributivity2_in(),		rewriteDistributivity2_in },
		{ distributivity2_out(),	rewriteDistributivity2_out },

		{ doubleNegationPattern(),	rewriteDoubleNegation },
		{ implicationPattern(),		rewriteImplication },
		{ equivalencePattern(),		rewriteEquivalence },
		{ deMorgans1Pattern(),		rewriteDeMorgans1 },
		{ deMorgans2Pattern(),		rewriteDeMorgans2 },
	};
	for (const auto& [pattern, functor] : patternMap)
		if (tree == pattern)
			return functor(tree);
	return tree;
}

ast::tree& negation_normal_form(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	tree = rewrite(tree);
	// std::cout << "\n--\n";
	// printTree(tree);
	// std::cout << "--\n";
	switch (tree.size())
	{
		case 2: negation_normal_form(tree.snd_child());
		case 1: negation_normal_form(tree.fst_child());
	}
	return tree;
}

std::string negation_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
	{
		std::cerr << "Invalid formula \"" << s << "\"\n";
		return s;
	}
	std::cout << "Before\n";
	printTree(maybeTree.value());
	auto nnfTree = negation_normal_form(maybeTree.value());
	std::cout << "\nAfter\n";
	printTree(nnfTree);
	return ast::treeToString(nnfTree);
}

void testRecog()
{
	auto t = ast::tree('=').add_two('|', 'A');
	t.fst_child().add_two('C', 'O');
	std::cout << "Before\n";
	printTree(t);
	auto b = rewrite(t);
	std::cout << "\nAfter\n";
	printTree(b);
}

void testDeM1()
{
	auto t = ast::tree('!').add_child('|');
	t.fst_child().add_child('A');
	t.fst_child().add_child('B');
	std::cout << "Before\n";
	printTree(t);
	auto b = rewrite(t);
	std::cout << "\nAfter\n";
	printTree(b);
}

void testNNF(const std::string& s)
{
	auto n = negation_normal_form(s);
	std::cout << "Transformed:\n";
	std::cout << n << '\n';
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
	testNNF("AB&!");
	testNNF("AB!|C&!");

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

