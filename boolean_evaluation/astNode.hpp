#pragma once
#include <memory>

#include <iostream>

enum NodeType
{
	Value,
	Operator,
};

struct IAstNode
{
	std::shared_ptr<IAstNode>	left;
	std::shared_ptr<IAstNode>	right;
	const char					value;
	const NodeType				type;

	IAstNode(char v, NodeType t): value(v), type(t) {}
	virtual int exec() const = 0;
	virtual ~IAstNode() {}
};

struct TrueNode : IAstNode
{
	int exec() const override
	{
		return 1;
	}
	TrueNode(): IAstNode('1', NodeType::Value) {}
};

struct FalseNode : IAstNode
{
	int exec() const override
	{
		return 0;
	}
	FalseNode(): IAstNode('0', NodeType::Value) {}
};

struct NotNode : IAstNode
{
	int exec() const override; // TODO
	NotNode(): IAstNode('!', NodeType::Operator) {}
};

struct AndNode : IAstNode
{
	int exec() const override
	{
		return left->exec() & right->exec();
	}
	AndNode(): IAstNode('&', NodeType::Operator) {}
};

struct OrNode : IAstNode
{
	int exec() const override
	{
		return left->exec() | right->exec();
	}
	OrNode(): IAstNode('|', NodeType::Operator) {}
};

struct XorNode : IAstNode
{
	int exec() const override
	{
		return left->exec() ^ right->exec();
	}
	XorNode(): IAstNode('^', NodeType::Operator) {}
};

struct CondNode : IAstNode
{
	int exec() const override
	{
		return left->exec() ? right->exec() : 1;
	}
	CondNode(): IAstNode('>', NodeType::Operator) {}
};

struct EqNode : IAstNode
{
	int exec() const override
	{
		return left->exec() == right->exec();
	}
	EqNode(): IAstNode('=', NodeType::Operator) {}
};
