#include "CNFPattern.hpp"

namespace cnf::pattern {

// AB&C| ≡ CA|CB|&

const ast::tree docPatternR()
{
	ast::tree pattern('|');
	pattern.add_two(ast::placeholder, '&');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDocL(ast::tree& tree)
{
	auto c = tree.snd_child();
	auto b = tree.fst_child().fst_child();
	auto a = tree.fst_child().snd_child();
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_two(b, c);
	tree.snd_child().add_two(a, c);
	return tree;
}

// ABC&| ≡ CA|CB|&

const ast::tree docPatternL()
{
	ast::tree pattern('|');
	pattern.add_two('&', ast::placeholder);
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDocR(ast::tree& tree)
{
	auto c = tree.fst_child();
	auto b = tree.snd_child().fst_child();
	auto a = tree.snd_child().snd_child();
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_two(b, c);
	tree.snd_child().add_two(a, c);
	return tree;
}

// AB|C| ≡ ABC||

const ast::tree doubleDisjunctionPattern()
{
	ast::tree pattern('|');
	pattern.add_two(ast::placeholder, '|');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDoubleDisjunction(ast::tree& tree)
{
	auto c = tree.fst_child();
	auto b = tree.snd_child().fst_child();
	auto a = tree.snd_child().snd_child();
	tree = ast::tree('|').add_two('|', a);
	tree.fst_child().add_two(c, b);
	return tree;
}

// AB&C& ≡ ABC&&

const ast::tree doubleConjunctionPattern()
{
	ast::tree pattern('&');
	pattern.add_two(ast::placeholder, '&');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDoubleConjunction(ast::tree& tree)
{
	auto c = tree.fst_child();
	auto b = tree.snd_child().fst_child();
	auto a = tree.snd_child().snd_child();
	tree = ast::tree('&').add_two('&', a);
	tree.fst_child().add_two(c, b);
	return tree;
}

}
