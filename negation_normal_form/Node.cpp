#include "ASTree.hpp"

namespace ast {

tree::tree(int value) : value(value) {}

tree::tree(const tree& other) : value(other.value)
{
	assign(other.begin(), other.end());
}

tree& tree::operator= (const tree& other)
{
	value = other.value;
	assign(other.begin(), other.end());
	return *this;
}

tree& tree::fst_child() { return front(); }
const tree& tree::fst_child() const { return front(); }

tree& tree::snd_child() { return back(); }
const tree& tree::snd_child() const { return back(); }

bool tree::exec() const
{
	switch (value)
	{
		case '!': return !fst_child().exec();
		case '&': return fst_child().exec() && snd_child().exec();
		case '|': return fst_child().exec() || snd_child().exec();
		case '^': return fst_child().exec() != snd_child().exec();
		case '=': return fst_child().exec() == snd_child().exec();
		case '>': if (!fst_child().exec())
					  return true;
				  return snd_child().exec();
	}
	return value == '1';
}

std::string treeToString(const tree& tree, std::string acc)
{
	acc = char(tree.value) + acc;
	std::string fst, snd;
	switch (tree.size())
	{
		case 1: fst = treeToString(tree.fst_child());
				return fst + acc;
		case 2: fst = treeToString(tree.snd_child());
				snd = treeToString(tree.fst_child());
				return fst + snd + acc;
	}
	return acc;
}

bool operator== (const tree& lhs, const tree& rhs)
{
	if (rhs.value == placeholder || lhs.value == placeholder)
		return true;
	if (lhs.size() == 1 && rhs.size() == 1 && lhs.value == rhs.value)
		return lhs.fst_child() == rhs.fst_child();
	if (lhs.size() == 2 && rhs.size() == 2 && lhs.value == rhs.value)
		return lhs.fst_child() == rhs.fst_child() && lhs.snd_child() == rhs.snd_child();
	return lhs.value == rhs.value;
}

void tree::printValue(const std::string& pref, char value, bool isRight)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = []()
	{
		static auto i = 0u;
		static const std::string colors[] = { "\033[1;32m", "\033[1;33m", "\033[1;31m", "\033[1;35m" };
		return colors[i++ % 4];
	};
	std::cout << pref
			  << (isRight ? "⦧ " : "⦦ " )
			  << chooseColor() << '\'' << char(value) << '\'' << resetColor() << '\n';
}

void printTree(const std::string& pref, const tree& node, bool isRight)
{
	switch (node.size())
	{
		case 0: return tree::printValue(pref, node.value, isRight);
		case 1: tree::printValue(pref, node.value, isRight);
				return printTree(pref + (isRight ? "ᐧ  " : "   "), node.fst_child(), false);
		case 2: printTree(pref + (isRight ? "   " : "ᐧ  "), node.fst_child(), true);
				tree::printValue(pref, node.value, isRight);
				printTree(pref + (isRight ? "ᐧ  " : "   "), node.snd_child(), false);
	}
}

void printTree(const tree& node)
{
	printTree("", node, false);
}

} // namespace ast
