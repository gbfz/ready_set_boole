#include <iostream>

auto eval_unary(char value, char op) -> std::string
{
	switch (op)
	{
		case '!': return std::to_string(!(value == '1'));
		default: throw std::exception();
	}
}

auto replace_unary(std::string& s, auto op_pos) -> std::string&
{
	auto left = s.at(op_pos - 1);
	auto op	  = s.at(op_pos);
	return s.replace(op_pos - 1, 2, eval_unary(left, op));
}

auto eval_binary(char a, char op, char b) -> std::string
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

auto replace_binary(std::string& s, auto op_pos) -> std::string&
{
	auto left  = s.at(op_pos - 2);
	auto op	   = s.at(op_pos);
	auto right = s.at(op_pos - 1);
	return s.replace(op_pos - 2, 3, eval_binary(left, op, right));
}

auto evaluate_and_replace(std::string& s, auto op_pos) -> std::string&
{
	switch (s[op_pos])
	{
		case '&': case '|': case '^': case '>': case '=':
			return replace_binary(s, op_pos);
		case '!':
			return replace_unary(s, op_pos);
		default: throw std::exception();
	}
}

auto rpn_slide_evaluator(std::string s) -> bool
{
	auto op_pos = s.find_first_not_of("10");
	while (op_pos != std::string::npos)
	{
		s = evaluate_and_replace(s, op_pos);
		op_pos = s.find_first_not_of("10", op_pos - 2);
	}
	if (s.size() != 1)
		throw std::exception();
	return s[0] == '1';
}

auto eval_formula(const std::string& formula) -> bool
{
	try {
		return rpn_slide_evaluator(formula);
	} catch (...) {
		std::cerr << "Invalid formula: " << formula << '\n';
		return false;
	}
}
