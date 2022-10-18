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
		case '>': if (!fst_child().exec())
					  return true;
				  return snd_child().exec();
		case '=': return fst_child().exec() == snd_child().exec();
	}
	return value == '1';
}

/*
void Node::printValue(const std::string& pref, char value, Branch branch)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = []()
	{
		static auto i = 0u;
		static const std::string colors[] = { "\033[1;32m", "\033[1;33m", "\033[1;31m", "\033[1;35m" };
		return colors[i++ % 4];
	};
	// std::cout << prefix << (isRight ? "⦦ " : "⦧ " )
	std::cout << pref
			  << (branch == Branch::right ? "⦧ " : "⦦ " )
			  << chooseColor()
			  << '\'' << char(value) << '\''
			  << resetColor() << '\n';
}
*/

/*
void Node::printValue(const std::string& prefix, char value, bool isRight)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = []()
	{
		static auto i = 0u;
		static const std::string colors[] = { "\033[1;32m", "\033[1;33m", "\033[1;31m", "\033[1;35m" };
		return colors[i++ % 4];
	};
	std::cout << prefix << (isRight ? "⦧ " : "⦦ " )
	// std::cout << prefix << (isRight ? "⦦ " : "⦧ " )
			  << chooseColor() << '\'' << char(value) << '\'' << resetColor() << '\n';
}
*/

void Node::printValue(int tab, char value)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = [](int tab)
	{
		static const char* colors[] = { "\033[1;36m", "\033[1;34m", "\033[1;33m", "\033[1;32m", "\033[1;35m" };
		return colors[tab % 5];
	};
	std::cout << chooseColor(tab)
			  << std::string(tab, ' ')
			  << char(value)
			  << resetColor() << '\n';
}

} // namespace AST
