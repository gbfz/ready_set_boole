#include "ASTree.hpp"

namespace AST {

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
	return value == '1';
}

} // namespace AST
