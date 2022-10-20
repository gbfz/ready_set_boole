#include "NNForm.hpp"

ast::tree& nnf::detail::rewrite(ast::tree& tree)
{
	using namespace nnf::pattern;
	using funcT = decltype(&rewriteDoubleNegation);
	static const std::vector<std::pair<ast::tree, funcT>> map =
	{
		{ implicationPattern(),		rewriteImplication		},
		{ equivalencePattern(),		rewriteEquivalence		},
		{ deMorgans1Pattern(),		rewriteDeMorgans1		},
		{ deMorgans2Pattern(),		rewriteDeMorgans2		},
		{ doubleNegationPattern(),	rewriteDoubleNegation	},
	};
	for (const auto& [pattern, functor] : map)
	{
		if (tree == pattern)
		{
			if (tree.value == '!')
				return negation_normal_form(functor(tree));
			return functor(tree);
		}
	}
	return tree;
}

ast::tree& nnf::detail::negation_normal_form(ast::tree& tree)
{
	tree = rewrite(tree);
	switch (tree.size())
	{
		case 0:
			return tree;
		case 1:
			rewrite(tree.fst_child());
			break;
		case 2:
			negation_normal_form(tree.fst_child());
			negation_normal_form(tree.snd_child());
			break;
	}
	return rewrite(tree);
}

std::string nnf::negation_normal_form(const std::string& s)
{
	auto maybeTree = ast::generateTree(s);
	if (!maybeTree)
		return "Invalid formula: " + s;
	auto nnfTree = detail::negation_normal_form(*maybeTree);
	return ast::treeToString(nnfTree);
}

void testNNF(const std::string& s)
{
	std::cout << "Transforming: " << s << '\n';
	auto n = nnf::negation_normal_form(s);
	std::cout << "Transformed : " << n << '\n';
	// std::cout << std::boolalpha << ast::generateTree(n).value().exec() << '\n';
}

int main()
{
	// testNNF("AB|C&!");
	// testNNF("AB|C=");
	// testNNF("AB|C>");
	// testNNF("AB&!");
	// testNNF("AB!|C&!");
	testNNF("AB|C&D=X>"); // AB|C&D!&A!B!&C!|D&|X|
	// testNNF("11|1&1=1>");
}
