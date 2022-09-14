#include "ast.hpp"
#include "astNode.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>

using std::make_shared;

std::shared_ptr<IAstNode> Ast::choose(char c)
{
	switch (c)
	{
		case '0': return make_shared<FalseNode>();
		case '1': return make_shared<TrueNode >();
		case '&': return make_shared<AndNode  >();
		case '|': return make_shared<OrNode   >();
		case '^': return make_shared<XorNode  >();
		case '>': return make_shared<CondNode >();
		case '=': return make_shared<EqNode   >();
	}
	throw std::runtime_error("Unknown token");
}

void Ast::insert(Nodeptr& where, Nodeptr&& node)
{
	if (!where) {
		where = node;
		return;
	}
	if (!where->right)
		return insert(where->right, std::move(node));
	if (!where->left)
		return insert(where->left, std::move(node));
	if (node->type == Value) {
		if (where->right->type == Operator)
			return insert(where->right, std::move(node));
		if (where->left->type == Operator)
			return insert(where->left, std::move(node));
	}
	// throw std::runtime_error("What");
}

bool Ast::is_valid(Nodeptr node) const
{
	if (!node)
		return true;
	if (node->type == Operator) {
		if (!(node->left && node->right))
			return false;
	}
	return is_valid(node->left) && is_valid(node->right);
}

bool Ast::is_valid() const
{
	return is_valid(root);
}

Ast& Ast::build(std::string s)
{
	// for (char c : s | std::ranges::views::reverse) {
	std::reverse(s.begin(), s.end());
	for (char c : s)
		insert(root, choose(c));
	if (!is_valid(root))
		throw std::runtime_error("Invalid formula");
	return *this;
}

bool Ast::exec() const
{
	if (!root)
		throw std::runtime_error("No ast to exec");
	return root->exec();
}

void Ast::print(std::shared_ptr<IAstNode> node, size_t offt) const
{
	if (!node)
		return;
	print(node->right, offt + 2);
	std::cout << std::string(offt + 1, ' ') << node->value << '\n';
	print(node->left, offt + 2);
}

const Ast& Ast::print() const
{
	print(root, 0);
	return *this;
}

void Ast::reset()
{
	root.reset();
}
