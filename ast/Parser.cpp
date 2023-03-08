#include "ASTree.hpp"
#include <bits/utility.h>

namespace ast::detail {

bool is_binop(char c)
{
	for (char e : "&|^>=")
		if (c == e)
			return true;
	return false;
}

bool is_operand(char c)
{
	return std::isalnum(c);
}

ast::tree generateTree(std::string& s, ast::tree& node)
{
	if (is_operand(node.value))
		return node;
	node.add_one(s.back());
	s.pop_back();
	generateTree(s, node.fst_child());
	if (is_binop(node.value))
	{
		node.add_one(s.back());
		s.pop_back();
		generateTree(s, node.snd_child());
	}
	return node;
}

} // namespace astParser::detail

namespace ast {

std::optional<tree> generateTree(std::string s)
{
	if (!validate(s))
		return {};
	ast::tree root(s.back());
	s.pop_back();
	return detail::generateTree(s, root);
}

bool validate(const std::string& s)
{
	auto sz = 0;
	for (char c : s)
	{
		if (detail::is_binop(c))
			sz -= 1;
		else if (detail::is_operand(c))
			sz += 1;
		if (sz <= 0)
			return false;
	}
	return sz == 1;
}

} // namespace astParser
