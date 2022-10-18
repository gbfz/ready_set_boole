#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <optional>
#include <queue>
#include <unistd.h>
#include <iostream>

namespace AST
{

bool validate(const std::string& s);
std::optional<struct Node> generateTree(std::string s);

struct Node : protected std::vector<Node>
{
	int value;

	Node(int value) : value(value) {}

	void add_child(int value);

	Node& fst_child();
	const Node& fst_child() const;

	Node& snd_child();
	const Node& snd_child() const;

	bool exec() const;

	/*
	friend void printTree(const std::string& pref, const Node& node, bool isRight = false)
	{
		switch (node.size())
		{
			case 0:
				return printValue(pref, node.value, isRight);
			case 1:
				printValue(pref, node.value, isRight);
				return printTree(pref + (isRight ? "ᐧ  " : "   "), node.fst_child(), false);
			case 2:
				printTree(pref + (isRight ? "   " : "ᐧ  "), node.fst_child(), true);
				printValue(pref, node.value, isRight);
				printTree(pref + (isRight ? "ᐧ  " : "   "), node.snd_child(), false);
		}
	}

	friend void printTree(const Node& node)
	{
		printTree("", node);
	}
	*/

	friend void printTree(const Node& node, int tab = 0) noexcept
	{
		if (node.empty())
			return printValue(tab, node.value);
		else if (node.size() == 1)
		{
			printValue(tab, node.value);
			return printTree(node.fst_child(), tab + 2);
		}
		printTree(node.fst_child(), tab + 2);
		printValue(tab, node.value);
		printTree(node.snd_child(), tab + 2);
	}

private:
	// static void printValue(const std::string& prefix, char value, Direction dir);
	// static void printValue(const std::string& prefix, char value, bool isRight);
	static void printValue(int tab, char value);
};

} // namespace AST
