#pragma once
#include <vector>
#include <optional>
#include <iostream>

namespace ast
{

bool validate(const std::string& s);
std::optional<class tree> generateTree(std::string s);
std::string treeToString(const ast::tree& tree, std::string acc = "");

static constexpr char placeholder = '\0';

class tree
{
private:
	std::vector<tree> m_branches;

public:
	char value = ast::placeholder;

	tree() = default;
	tree(char value);
	friend bool operator== (const tree& lhs, const tree& rhs);

	template <class Node>
	tree& add_one(Node&& n)
	{
		m_branches.emplace_back(std::forward<Node>(n));
		return *this;
	}

	template <class NodeA, class NodeB>
	tree& add_two(NodeA&& fst, NodeB&& snd)
	{
		m_branches.emplace_back(std::forward<NodeA>(fst));
		m_branches.emplace_back(std::forward<NodeB>(snd));
		return *this;
	}

	size_t size() const;
	bool empty() const;

	tree& fst_child();
	const tree& fst_child() const;

	tree& snd_child();
	const tree& snd_child() const;

	bool exec() const;

	friend void printTree(const std::string& pref, const tree& node, bool isRight);
	friend void print(const tree& node);
	static void printValue(const std::string& prefix, char value, bool isRight);
};

} // namespace ast
