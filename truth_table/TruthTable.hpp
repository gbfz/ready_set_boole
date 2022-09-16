#pragma once
#include <exception>
#include <map>
#include <vector>
#include <iostream>
#include "RpnEvaluator.hpp"

class TruthTable
{
	using Table = std::map<char, std::vector<int>>;
	using Iter = std::vector<int>::iterator;

	Table				table;
	std::string			formula;
	std::vector<int>	results;
	int					row_count;

	auto fill_table() -> void;
	auto fill_column(Iter start, Iter end, int step, int filler) -> void;
	auto calculate_results() -> void;

	auto create_formula(int row_index) const -> std::string;

	auto is_formula_valid() const -> bool;

	auto power2n(int n) const -> int;
	auto count_variables() const -> int;

public:
	TruthTable(const std::string& s);
	auto get_results() const -> std::vector<int>;
	auto print() const -> void;
};
