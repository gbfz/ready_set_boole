#pragma once
#include "astNode.hpp"

class Ast
{
	std::shared_ptr<IAstNode> root;
	void insert(std::shared_ptr<IAstNode>& node);
	void insert(std::shared_ptr<IAstNode>& where,
				std::shared_ptr<IAstNode>& node);
	std::shared_ptr<IAstNode> choose(char c);
	void print(std::shared_ptr<IAstNode> node, size_t offt) const;
public:
	void build(std::string s);
	bool exec() const;
	void print() const;
};
