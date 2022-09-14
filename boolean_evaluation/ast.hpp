#pragma once
#include "astNode.hpp"

class Ast
{
	using Nodeptr = std::shared_ptr<IAstNode>;
	Nodeptr 	root;

	void		insert(Nodeptr& where, Nodeptr&& node);
	Nodeptr		choose(char c);
	void		print(Nodeptr node, size_t offt) const;
	bool 		is_valid(Nodeptr node) const;
public:
	Ast&		build(std::string s);
	bool		is_valid() const;
	bool		exec() const;
	const Ast&	print() const;
	void		reset();
};
