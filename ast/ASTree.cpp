#include "ASTree.hpp"

void Node::add_child(int value)
{
	emplace_back(value);
}

Node& Node::fst_child()
{
	return front();
}

const Node& Node::fst_child() const
{
	return front();
}

Node& Node::snd_child()
{
	return back();
}

const Node& Node::snd_child() const
{
	return back();
}

bool Node::exec() const
{
	switch (value)
	{
		case '!': return !fst_child().exec();
		case '&': return fst_child().exec() && snd_child().exec();
		case '|': return fst_child().exec() || snd_child().exec();
		case '^': return fst_child().exec() != snd_child().exec();
		case '>': if (!fst_child().exec()) return true;
		          else return snd_child().exec();
		case '=': return fst_child().exec() == snd_child().exec();
	}
	return value;
}

bool Parser::is_binop(char c)
{
	for (char e : "&|^>=")
		if (c == e)
			return true;
	return false;
}

ASTree Parser::generateTree(std::string& s, Node& node)
{
	if (s.empty() || std::isdigit(node.value))
		return node;
	node.add_child(s.back());
	s.pop_back();
	generateTree(s, node.fst_child());
	if (is_binop(node.value))
	{
		node.add_child(s.back());
		s.pop_back();
		generateTree(s, node.snd_child());
	}
	return node;
}

std::optional<ASTree> Parser::generateTree(std::string s)
{
	if (!validate(s))
		return {};
	Node root(s.back());
	s.pop_back();
	return generateTree(s, root);
}

bool Parser::validate(const std::string& s)
{
	auto sz = 0;
	for (char c : s)
	{
		if (is_binop(c))
			sz -= 1;
		else if (std::isdigit(c))
			sz += 1;
		if (sz <= 0)
			return false;
	}
	return sz == 1;
}
