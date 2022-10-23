#include "CNFPattern.hpp"

namespace cnf::pattern {

// Distributivity 1 | conOverDis: AB|C& ≡ AB|AC|&
// Distributivity 2 | disOverCon: AB&C| ≡ AB&AC&|

const ast::tree disOverConPattern()
{
	ast::tree pattern('|');
	pattern.add_two(ast::placeholder, '&');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDisOverCon(ast::tree& tree)
{
	auto a = tree.fst_child();
	auto b = tree.snd_child().fst_child();
	auto c = tree.snd_child().snd_child();
	tree = ast::tree('|').add_two('&', '&');
	tree.fst_child().add_two(c, a);
	tree.snd_child().add_two(b, a);
	return tree;
}

}
