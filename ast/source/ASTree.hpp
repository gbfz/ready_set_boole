#pragma once
#include <vector>
#include <optional>
#include <iostream>

namespace ast
{

bool validate(const std::string& s);
std::optional<struct tree> generateTree(std::string s);
std::string treeToString(const ast::tree& tree, std::string acc = "");

static constexpr char placeholder = '\0';

struct tree : public std::vector<tree>
{
	int value;

	tree() = default;
	tree(int value);
	tree(const tree& other);
	tree& operator= (const tree& other);
	friend bool operator== (const tree& lhs, const tree& rhs);

	template <class Node>
	tree& add_one(Node&& n)
	{
		emplace_back(std::forward<Node>(n));
		return *this;
	}

	template <class NodeA, class NodeB>
	tree& add_two(NodeA&& fst, NodeB&& snd)
	{
		emplace_back(std::forward<NodeA>(fst));
		emplace_back(std::forward<NodeB>(snd));
		return *this;
	}

	tree& fst_child();
	const tree& fst_child() const;

	tree& snd_child();
	const tree& snd_child() const;

	bool exec() const;

	friend void printTree(const std::string& pref, const tree& node, bool isRight);
	friend void printTree(const tree& node);
	static void printValue(const std::string& prefix, char value, bool isRight);
};

} // namespace ast
