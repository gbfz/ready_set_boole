#include "RpnEvaluator.hpp"
#include <iostream>

RpnEvaluator::RpnEvaluator(const std::string& s)
	: formula(s)
{}

auto RpnEvaluator::evaluate() -> bool
{
	try {
		return RpnEvaluator::rpn_slide_evaluator();
	} catch (std::exception& e) {
		std::cerr << "Invalid formula: " << formula << " : " << e.what() << '\n';
		return false;
	}
}

auto RpnEvaluator::rpn_slide_evaluator() -> bool
{
	auto op_pos = formula.find_first_not_of("10");
	while (op_pos != std::string::npos)
	{
		formula = evaluate_and_replace(op_pos);
		op_pos = formula.find_first_not_of("10");
	}
	if (formula.size() != 1)
		throw std::runtime_error("excess symbols: " + formula);
	return formula[0] == '1';
}

auto RpnEvaluator::evaluate_and_replace(auto op_pos) -> std::string&
{
	switch (formula[op_pos])
	{
		case '&': case '|': case '^': case '>': case '=':
			return replace_binary(op_pos);
		case '!':
			return replace_unary(op_pos);
		default: throw std::runtime_error("unknown operator " + std::to_string(formula[op_pos]));
	}
}

auto RpnEvaluator::eval_unary(char value, char op) -> std::string
{
	switch (op)
	{
		case '!': return std::to_string(!(value == '1'));
		default: throw std::exception();
	}
}

auto RpnEvaluator::replace_unary(auto op_pos) -> std::string&
{
	auto left = formula.at(op_pos - 1);
	auto op	  = formula.at(op_pos);
	return formula.replace(op_pos - 1, 2, eval_unary(left, op));
}

auto RpnEvaluator::eval_binary(char a, char op, char b) -> std::string
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

auto RpnEvaluator::replace_binary(auto op_pos) -> std::string&
{
	auto left  = formula.at(op_pos - 2);
	auto op	   = formula.at(op_pos);
	auto right = formula.at(op_pos - 1);
	return formula.replace(op_pos - 2, 3, eval_binary(left, op, right));
}
