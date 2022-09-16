#pragma once
#include <string>

class RpnEvaluator
{
	std::string formula;

	auto rpn_slide_evaluator(std::string s) const -> bool;
	auto evaluate_and_replace(std::string& s, auto op_pos) const -> std::string&;

	auto replace_binary(std::string& s, auto op_pos) const -> std::string&;
	auto eval_binary(char a, char op, char b) const -> std::string;

	auto replace_unary(std::string& s, auto op_pos) const -> std::string&;
	auto eval_unary(char value, char op) const -> std::string;
public:
	RpnEvaluator(const std::string& f);
	auto evaluate() const -> bool;
};
