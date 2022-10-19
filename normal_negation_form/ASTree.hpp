#pragma once
#include <vector>
#include <string>
#include <optional>
#include <iostream>

namespace ast
{

bool validate(const std::string& s);
std::optional<struct tree> generateTree(std::string s);

static constexpr char placeholder = '\0';
struct placeholder_t {};

struct tree : protected std::vector<tree>
{
	int value;

	tree(int value) : value(value) {}

	tree& add_child(tree& other);
	tree& add_two(tree& fst, tree& snd);

	tree& add_child(int value);
	tree& add_two(int v1, int v2);
	tree& add_two(placeholder_t, placeholder_t);

	tree& fst_child();
	const tree& fst_child() const;

	tree& snd_child();
	const tree& snd_child() const;

	bool exec() const;

	tree& operator= (const tree& other);

	friend bool operator== (const tree& lhs, const tree& rhs);
	// friend bool operator== (const tree& tree, placeholder_t);
	bool operator== (placeholder_t)
	{
		return true;
	}

	friend void printTree(const std::string& pref, const tree& node, bool isRight = false)
	{
		switch (node.size())
		{
			case 0: return printValue(pref, node.value, isRight);
			case 1: printValue(pref, node.value, isRight);
					return printTree(pref + (isRight ? "ᐧ  " : "   "), node.fst_child(), false);
			case 2: printTree(pref + (isRight ? "   " : "ᐧ  "), node.fst_child(), true);
					printValue(pref, node.value, isRight);
					printTree(pref + (isRight ? "ᐧ  " : "   "), node.snd_child(), false);
		}
	}

	friend void printTree(const tree& node)
	{
		printTree("", node);
	}

	/*
	friend void printTree(const tree& node, int tab = 0) 
	{
		switch (node.size())
		{
			case 0: return printValue(tab, node.value);
			case 1: printValue(tab, node.value);
					return printTree(node.fst_child(), tab + 2);
			case 2: printTree(node.fst_child(), tab + 2);
					printValue(tab, node.value);
					return printTree(node.snd_child(), tab + 2);
		}
	}
	*/

private:
	static void printValue(const std::string& prefix, char value, bool isRight);
	// static void printValue(int tab, char value);
};

} // namespace ast
