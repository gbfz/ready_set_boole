#include "ast.hpp"
#include "astNode.hpp"
#include <stdexcept>
#include <algorithm>
#include <typeinfo>

using std::shared_ptr, std::make_shared;

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

void Ast::insert(shared_ptr<IAstNode>& where,
				 shared_ptr<IAstNode>& node)
{
	if (!where) {
		where = node;
		return;
	}
	if (where->type == Operator && node->type == Operator) {
		if (!where->right)
			return insert(where->right, node);
		return insert(where->left, node);
	}
	if (!where->left)
		return insert(where->left, node);
	return insert(where->right, node);
}

void Ast::insert(std::shared_ptr<IAstNode>& node)
{
	insert(root, node);
}

void Ast::build(std::string s)
{
	// for (char c : s | std::views::reverse) {
	std::reverse(s.begin(), s.end());
	for (char c : s) {
		auto node = choose(c);
		insert(node);
	}
}

bool Ast::exec() const
{
	if (!root)
		throw std::runtime_error("No ast to exec");
	return root->exec();
}

#include <iostream>

void Ast::print(std::shared_ptr<IAstNode> node, size_t offt) const
{
	if (!node)
		return;
	print(node->right, offt + 2);
	std::cout << std::string(offt + 1, ' ') << node->value << '\n';
	print(node->left, offt + 2);
}

void Ast::print() const
{
	print(root, 0);
}
