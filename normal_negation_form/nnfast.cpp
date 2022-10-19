// #include "../ast/source/ASTree.hpp"
#include "ASTree.hpp"
#include <functional>
#include <unordered_map>
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
	pattern.add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeEquivalence(const ast::tree& node)
{
	static const ast::tree pattern = equivalencePattern();
	return node == pattern;
}

const ast::tree deMorgans1()
{
	ast::tree pattern('!');
	pattern.add_child('|');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeDeMorgan1(const ast::tree& node)
{
	static const ast::tree pattern = deMorgans1();
	return node == pattern;
}

const ast::tree deMorgans2()
{
	ast::tree pattern('!');
	pattern.add_child('&');
	pattern.fst_child().add_two(ast::placeholder, ast::placeholder);
	return pattern;
}

bool recognizeDeMorgan2(const ast::tree& node)
{
	static const ast::tree pattern = deMorgans2();
	return node == pattern;
}

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

ast::tree& rewriteDoubleNegation(ast::tree& tree)
{
	tree = tree.fst_child().fst_child();
	return tree;
}

ast::tree& rewriteImplication(ast::tree& tree)
{
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('|').add_child(snd);
	tree.snd_child() = ast::tree('!').add_child(fst);
	return tree;
}

ast::tree& rewriteEquivalence(ast::tree& tree)
{
	auto fst = tree.fst_child();
	auto snd = tree.snd_child();
	tree = ast::tree('&').add_two('|', '|');
	tree.fst_child().add_child('!');
	tree.fst_child().fst_child().add_child(fst);
	tree.fst_child().add_child(snd);
	tree.snd_child().add_child(fst);
	tree.snd_child().add_child('!');
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

ast::tree& rewriteDeMorgans1(ast::tree& tree)
{
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('&').add_two('!', '!');
	tree.fst_child().add_child(fst);
	tree.snd_child().add_child(snd);
	return tree;
}

ast::tree& rewriteDeMorgans2(ast::tree& tree)
{
	auto fst = tree.fst_child().fst_child();
	auto snd = tree.fst_child().snd_child();
	tree = ast::tree('|').add_two('!', '!');
	tree.fst_child().add_child(fst);
	tree.snd_child().add_child(snd);
	return tree;
}

ast::tree& rewrite(ast::tree& tree)
{
	using modifierT = std::function<ast::tree&(ast::tree&)>;
	static const std::unordered_map<ast::tree, modifierT, hashTree> converter =
	{
		{ doubleNegationPattern(),	rewriteDoubleNegation },
		{ implicationPattern(),		rewriteImplication },
		{ equivalencePattern(),		rewriteEquivalence },
		{ deMorgans1(),				rewriteDeMorgans1 },
		{ deMorgans2(),				rewriteDeMorgans2 }
	};
	for (const auto& [pattern, functor] : converter)
		if (tree == pattern)
			return functor(tree);
	return tree;
}

ast::tree& negation_normal_form(ast::tree& tree)
{
	if (tree.empty())
		return tree;
	tree = rewrite(tree);
	switch (tree.size())
	{
		case 2: negation_normal_form(tree.snd_child());
		case 1: negation_normal_form(tree.fst_child());
	}
	return tree;
}

void test1()
{
	auto t = ast::tree('=').add_child('A').add_child('B');
	if (recognizeEquivalence(t))
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
	auto b = rewriteEquivalence(t);
	std::cout << "\nAfter\n";
	printTree(b);
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

void testNNF()
{
	auto t = ast::tree('!').add_child('|');
	t.fst_child().add_child('!');
	t.fst_child().fst_child().add_child('!');
	t.fst_child().fst_child().fst_child().add_child('A');
	t.fst_child().add_child('B');
	std::cout << "Before\n";
	printTree(t);
	auto b = negation_normal_form(t);
	std::cout << "\nAfter\n";
	printTree(b);
}

void testNNF(const std::string& s)
{
	auto maybeT = ast::generateTree(s);
	if (!maybeT)
		return;
	auto t = *maybeT;
	std::cout << "Before\n";
	printTree(t);
	std::cout << std::boolalpha << t.exec() << '\n';
	auto b = negation_normal_form(t);
	std::cout << "\nAfter\n";
	printTree(b);
	std::cout << std::boolalpha << b.exec() << '\n';
}

 // * De Morgan's I:		AB|!	≡	A!B!&
int main()
{
	// test2();
	// testREq();
	// testRecog();
	// testDeM1();
	// testNNF();
	// testNNF("AB|C&!");
	testNNF("AB|C=");
}
