// #include "../ast/source/ASTree.hpp"
#include "ASTree.hpp"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

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

enum class Pattern
{
	DoubleNegation,
	Implication,
	Equivalence,
	DeMorgans1,
	DeMorgans2,
	None
};

const ast::tree doubleNegationPattern()
{
	ast::tree pattern('!');
	pattern.add_child('!');
	pattern.fst_child().add_child(ast::placeholder);
	return pattern;
}

bool recognizeDoubleNegation(const ast::tree& node)
{
	static const ast::tree pattern = doubleNegationPattern();
	return node == pattern;
}

const ast::tree implicationPattern()
{
	ast::tree pattern('>');
	pattern.add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeImplication(const ast::tree& node)
{
	static const ast::tree pattern = implicationPattern();
	return node == pattern;
}

const ast::tree equivalencePattern()
{
	ast::tree pattern('=');
	pattern.add_two(ast::placeholder_t{}, ast::placeholder_t{});
	return pattern;
}

bool recognizeEquivalence(const ast::tree& node)
{
	static const ast::tree pattern = equivalencePattern();
	return node == pattern;
}

const ast::tree deMorganI()
{
	ast::tree pattern('!');
	pattern.add_child('|');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeDeMorgan1(const ast::tree& node)
{
	static const ast::tree pattern = deMorganI();
	return node == pattern;
}

const ast::tree deMorgan2()
{
	ast::tree pattern('!');
	pattern.add_child('&');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeDeMorgan2(const ast::tree& node)
{
	static const ast::tree pattern = deMorgan2();
	return node == pattern;
}

Pattern matchPattern(const ast::tree& tree)
{
	using cmpType = std::function<bool(const ast::tree&)>;
	const std::array<cmpType, 5> cmps = {
						recognizeDoubleNegation
					  , recognizeImplication
					  , recognizeEquivalence
					  , recognizeDeMorgan1
					  , recognizeDeMorgan2
	};
	static constexpr Pattern patterns[] = {
						Pattern::DoubleNegation
					  , Pattern::Implication
					  , Pattern::Equivalence
					  , Pattern::DeMorgans1
					  , Pattern::DeMorgans2
	};
	for (auto i = 0; i < cmps.size(); ++i)
		if (cmps[i](tree))
			return patterns[i];
	return Pattern::None;
}

ast::tree& replaceDoubleNegation(ast::tree& tree)
{
	tree = tree.fst_child().fst_child();
	return tree;
}

ast::tree& replaceImplication(ast::tree& tree)
{
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('|').add_child(snd);
	tree.snd_child() = ast::tree('!').add_child(fst);
	return tree;
}

ast::tree& replaceEquivalence(ast::tree& tree)
{
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('|').add_two('&', '&');
	tree.fst_child().add_two('!', '!');
	tree.fst_child().fst_child().add_child(fst);
	tree.fst_child().snd_child().add_child(snd);
	tree.snd_child().add_two(fst, snd);
	return tree;
}

void test1()
{
	auto t = ast::tree('=').add_child('A').add_child('B');
	if( recognizeEquivalence(t))
		std::cout << "Yeah\n";
	else std::cout << "No\n";
}

void test2()
{
	auto t = ast::tree('!').add_child('|');
	t.fst_child().add_two('B', 'A');
	if (recognizeDeMorgan1(t))
		std::cout << "Yeah\n";
	else std::cout << "No\n";
}

void testREq()
{
	auto t = ast::tree('=').add_two('|', 'A');
	// auto t = ast::tree('=').add_child('!').add_child('!');
	// t.fst_child().add_child('A');
	// t.snd_child().add_child('|');
	// t.snd_child().fst_child().add_two('C', 'O');
	t.fst_child().add_two('C', 'O');
	std::cout << "Before\n";
	printTree(t);
	auto b = replaceEquivalence(t);
	std::cout << "\nAfter\n";
	printTree(b);
}

 // * De Morgan's I:		AB|!	≡	A!B!&
int main()
{
	// test2();
	testREq();
}
