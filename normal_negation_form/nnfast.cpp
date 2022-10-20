#include "ASTree.hpp"
#include "Pattern.hpp"
#include <unordered_map>

template <>
struct std::hash<ast::tree>
{
	size_t operator()(const ast::tree&node) const
	{
		auto hasher = std::hash<size_t>();
		auto fst = hasher(node.value) + hasher(node.size());
		switch (node.size())
		{
			case 0: return fst;
			case 1: return fst
				   		 + hasher(node.fst_child().value) + hasher(node.fst_child().size());
			case 2: return fst 
						 + hasher(node.fst_child().value) + hasher(node.fst_child().size())
						 + hasher(node.snd_child().value) + hasher(node.snd_child().size());
		}
		return std::string::npos;
	}
};

ast::tree& negation_normal_form(ast::tree& tree);

ast::tree& rewrite(ast::tree& tree, bool recall = false)
{
	using namespace pattern;
	using PatternActionMap = std::unordered_map<ast::tree, decltype(&rewriteDoubleNegation)>;
	static const PatternActionMap map =
	{
		{ doubleNegationPattern(),	rewriteDoubleNegation },
		{ implicationPattern(),		rewriteImplication },
		{ equivalencePattern(),		rewriteEquivalence },
		{ deMorgans1Pattern(),		rewriteDeMorgans1 },
		{ deMorgans2Pattern(),		rewriteDeMorgans2 },
	};
	for (const auto& [pattern, functor] : map)
	{
		if (tree == pattern)
		{
			if (recall)
				return negation_normal_form(functor(tree));
			return functor(tree);
		}
	}
	return tree;
}
//  /\        /\        /\        /\        /\        /\        /\
   //\\      //\\      //\\      //\\      //\\      //\\      //\\
  //¯¯\\    //¯¯\\    //¯¯\\    //¯¯\\    //¯¯\\    //¯¯\\    //¯¯\\
 //¯¯¯¯\\  //¯¯¯¯\\  //¯¯¯¯\\  //¯¯¯¯\\  //¯¯¯¯\\  //¯¯¯¯\\  //¯¯¯¯\\
/*¯¯¯¯¯¯\\//¯¯¯¯¯¯\\//¯¯¯¯¯¯\\//¯¯¯¯¯¯\\//¯¯¯¯¯¯\\//¯¯¯¯¯¯\\//¯¯¯¯¯¯*/
/*¯¯¯¯¯¯ \/¯¯¯¯¯¯¯¯\/¯¯¯¯¯¯¯¯\/¯¯¯¯¯¯¯¯\/¯¯¯¯¯¯¯¯\/¯¯¯¯¯¯¯¯\/¯¯¯¯¯¯¯*/
/*   This whole "recall" thing is a mess, but here's why I need it: */
/*                                                                  */
/*   When dealing with single-child nodes - meaning the '!' nodes - */
/*   it's crucial to first rewrite the child, and then check        */
/*   the '!' node again as it is highly likely that some pattern    */
/*   emerged there after modifying the child.                       */
/*                                                                  */
/********************************************************************/

ast::tree& negation_normal_form(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	tree = rewrite(tree);
	switch (tree.size())
	{
		case 2: negation_normal_form(tree.fst_child());
				negation_normal_form(tree.snd_child());
				break;
		case 1: rewrite(tree.fst_child());
				break;
	}
	return rewrite(tree, true);
}

std::string negation_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
	{
		std::cerr << "\nInvalid formula \"" << s << "\"\n";
		return s;
	}
	std::cout << "\nTransforming " << s << '\n';
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
	// std::cout << std::boolalpha << ast::generateTree(n).value().exec() << '\n';
}

int main()
{
	// testNNF("AB|C&!");
	// testNNF("AB|C=");
	// testNNF("AB|C>");
	// testNNF("AB&!");
	// testNNF("AB!|C&!");
	// testNNF("AB|C&D=X>");
	testNNF("11|0&1=1>");
	// should ideally yield ((1 ⋅(1 + 1)) ↔ 1) → 0 :: 11|1&1=0>
}
