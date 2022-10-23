#include "NNFPattern.hpp"

namespace nnf::pattern {

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	A!B|AB!|&
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 * Distributivity I:	AB|C&	≡	CA&CB&|
 * Distributivity II:	AB&C|	≡	CA|CB|&
 */


const ast::tree doubleNegationPattern()
{
	ast::tree pattern('!');
	pattern.add_one('!');
	pattern.fst_child().add_one(ast::placeholder);
	return pattern;
}

ast::tree& rewriteDoubleNegation(ast::tree& tree)
{
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
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('|').add_two(fst, '!');
	tree.snd_child().add_one(snd);
	return tree;
}

const ast::tree equivalencePattern()
{
	ast::tree pattern('=');
	pattern.add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteEquivalence(ast::tree& tree)
{
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_two('!', snd);
	tree.fst_child().fst_child().add_one(fst);
	tree.snd_child().add_two(fst, '!');
	tree.snd_child().snd_child().add_one(snd);
	return tree;
}

const ast::tree deMorgans1Pattern()
{
	ast::tree pattern('!');
	pattern.add_one('|');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDeMorgans1(ast::tree& tree)
{
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('&').add_two('!', '!');
	tree.fst_child().add_one(fst);
	tree.snd_child().add_one(snd);
	return tree;
}

const ast::tree deMorgans2Pattern()
{
	ast::tree pattern('!');
	pattern.add_one('&');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

ast::tree& rewriteDeMorgans2(ast::tree& tree)
{
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('|').add_two('!', '!');
	tree.fst_child().add_one(fst);
	tree.snd_child().add_one(snd);
	return tree;
}

}
