#include "RpnEvaluator.hpp"
#include <iostream>

RpnEvaluator::RpnEvaluator(const std::string& s)
	: formula(s)
{}

auto RpnEvaluator::evaluate() const -> bool
{
	try {
		return RpnEvaluator::rpn_slide_evaluator(formula);
	} catch (std::exception& e) {
		std::cerr << "Invalid formula: " << formula << " : " << e.what() << '\n';
		return false;
	}
}

auto RpnEvaluator::rpn_slide_evaluator(std::string s) const -> bool
{
	auto op_pos = s.find_first_not_of("10");
	while (op_pos != std::string::npos)
	{
		s = evaluate_and_replace(s, op_pos);
		op_pos = s.find_first_not_of("10");
	}
	if (s.size() != 1)
		throw std::runtime_error("excess symbols : " + s);
	return s[0] == '1';
}

auto RpnEvaluator::evaluate_and_replace(std::string& s, auto op_pos) const -> std::string&
{
	switch (s[op_pos])
	{
		case '&': case '|': case '^': case '>': case '=':
			return replace_binary(s, op_pos);
		case '!':
			return replace_unary(s, op_pos);
		default: throw std::runtime_error("unknown operator " + std::to_string(s[op_pos]));
	}
}

auto RpnEvaluator::eval_unary(char value, char op) const -> std::string
{
	switch (op)
	{
		case '!': return std::to_string(!(value == '1'));
		default: throw std::exception();
	}
}

auto RpnEvaluator::replace_unary(std::string& s, auto op_pos) const -> std::string&
{
	auto left = s.at(op_pos - 1);
	auto op	  = s.at(op_pos);
	return s.replace(op_pos - 1, 2, eval_unary(left, op));
}

auto RpnEvaluator::eval_binary(char a, char op, char b) const -> std::string
{
	auto left = a - '0', right = b - '0';
	switch (op)
	{
		case '&': return std::to_string(left & right);
		case '|': return std::to_string(left | right);
		case '^': return std::to_string(left ^ right);
		case '>': return std::to_string(left ? right : 1);
		case '=': return std::to_string(left == right);
		default: throw std::exception();
	}
}

auto RpnEvaluator::replace_binary(std::string& s, auto op_pos) const -> std::string&
{
	auto left  = s.at(op_pos - 2);
	auto op	   = s.at(op_pos);
	auto right = s.at(op_pos - 1);
	return s.replace(op_pos - 2, 3, eval_binary(left, op, right));
}
