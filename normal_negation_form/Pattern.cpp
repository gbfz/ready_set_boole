#include "Pattern.hpp"

namespace pattern {

const ast::tree doubleNegationPattern()
{
	ast::tree pattern('!');
	pattern.add_child('!');
	pattern.fst_child().add_child(ast::placeholder);
	return pattern;
}

ast::tree& rewriteDoubleNegation(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	tree = tree.fst_child().fst_child();
	return tree;
}

const ast::tree implicationPattern()
{
	ast::tree pattern('>');
	pattern.add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteImplication(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('|').add_two(fst, '!');
	tree.snd_child().add_child(snd);
	return tree;
}

const ast::tree equivalencePattern()
{
	ast::tree pattern('=');
	pattern.add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

// A ≡ B :: (!A | B) & (A | !B)
// AB= :: A!B|AB!|&
ast::tree& rewriteEquivalence(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto fst = tree.fst_child(); //B
	auto snd = tree.snd_child(); //A
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_two('!', snd);
	tree.fst_child().fst_child().add_child(fst);
	tree.snd_child().add_two(fst, '!');
	tree.snd_child().snd_child().add_child(snd);
	/*
	tree = ast::tree('|').add_two('&', '&');
	tree.fst_child().add_two('!', '!');
	tree.fst_child().fst_child().add_child(fst);
	tree.fst_child().snd_child().add_child(snd);
	tree.snd_child().add_two(fst, snd);
	*/
	return tree;
}

const ast::tree deMorgans1Pattern()
{
	ast::tree pattern('!');
	pattern.add_child('|');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDeMorgans1(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('&').add_two('!', '!');
	tree.fst_child().add_child(fst);
	tree.snd_child().add_child(snd);
	return tree;
}

const ast::tree deMorgans2Pattern()
{
	ast::tree pattern('!');
	pattern.add_child('&');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDeMorgans2(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('|').add_two('!', '!');
	tree.fst_child().add_child(fst);
	tree.snd_child().add_child(snd);
	return tree;
}

const ast::tree distributivity1_in()
{
	ast::tree pattern('&');
	pattern.add_two(ast::placeholder, '|');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDistr1_in(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto a = tree.snd_child().snd_child();
	auto b = tree.snd_child().fst_child();
	auto c = tree.fst_child();
	tree = ast::tree('|').add_two('&', '&');
	tree.fst_child().add_two(b, c);
	tree.snd_child().add_two(a, c);
	return tree;
}

const ast::tree distributivity1_out()
{
	ast::tree pattern('|');
	pattern.add_two('&', '&');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDistr1_out(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto a = tree.snd_child().fst_child();
	auto b = tree.fst_child().fst_child();
	auto c = tree.fst_child().snd_child();
	tree = ast::tree('&').add_two(c, '|');
	tree.snd_child().add_two(b, a);
	return tree;
}

const ast::tree distributivity2_in()
{
	ast::tree pattern('|');
	pattern.add_two(ast::placeholder, '&');
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDistr2_in(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto a = tree.snd_child().snd_child();
	auto b = tree.snd_child().fst_child();
	auto c = tree.fst_child();
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_two(b, c);
	tree.snd_child().add_two(a, c);
	return tree;
}

const ast::tree distributivity2_out()
{
	ast::tree pattern('&');
	pattern.add_two('|', '|');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	pattern.snd_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDistr2_out(ast::tree& tree)
{
	std::cout << __FUNCTION__ << '\n';
	auto a = tree.snd_child().fst_child();
	auto b = tree.fst_child().fst_child();
	auto c = tree.fst_child().snd_child();
	tree = ast::tree('|').add_two(c, '&');
	tree.snd_child().add_two(b, a);
	return tree;
}

}
