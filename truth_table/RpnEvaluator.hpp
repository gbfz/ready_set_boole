#pragma once
#include <string>
#include <exception>

class RpnEvaluator
{
	std::string formula;

	auto rpn_slide_evaluator() -> bool;
	auto evaluate_and_replace(auto op_pos) -> std::string&;

	auto replace_binary(auto op_pos) -> std::string&;
	auto eval_binary(char a, char op, char b) -> std::string;

	auto replace_unary(auto op_pos) -> std::string&;
	auto eval_unary(char value, char op) -> std::string;
public:
	RpnEvaluator(const std::string& f);
	auto evaluate() -> bool;
};
