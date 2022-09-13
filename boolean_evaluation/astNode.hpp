#pragma once
#include <memory>

#include <iostream>

enum NodeType
{
	Value,
	Operator,
	None
};

struct IAstNode
{
	std::shared_ptr<IAstNode> left, right;
	virtual int exec() const = 0;
	virtual ~IAstNode() {}
	char value;
	NodeType type;
	IAstNode(char v, NodeType t): value(v), type(t) {}
};

struct TrueNode : virtual IAstNode
{
	int exec() const
	{
		return 1;
	}
	TrueNode(): IAstNode('1', Value) {}
};

struct FalseNode : virtual IAstNode
{
	int exec() const
	{
		return 0;
	}
	char value;
	FalseNode(): IAstNode('0', Value) {}
};

struct NotNode : IAstNode
{
	int exec() const; // TODO
	NotNode(): IAstNode('!', Operator) {}
};

struct AndNode : IAstNode
{
	int exec() const
	{
		return left->exec() & right->exec();
	}
	AndNode(): IAstNode('&', Operator) {}
};

struct OrNode : IAstNode
{
	int exec() const
	{
		return left->exec() | right->exec();
	}
	OrNode(): IAstNode('|', Operator) {}
};

struct XorNode : IAstNode
{
	int exec() const
	{
		return left->exec() ^ right->exec();
	}
	XorNode(): IAstNode('^', Operator) {}
};

struct CondNode : IAstNode
{
	int exec() const
	{
		return left->exec() ? right->exec() : 1;
	}
	CondNode(): IAstNode('>', Operator) {}
};

struct EqNode : IAstNode
{
	int exec() const
	{
		return left->exec() == right->exec();
	}
	EqNode(): IAstNode('=', Operator) {}
};
