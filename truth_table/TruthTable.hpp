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

	Table			table;
	std::string		formula;
	int				row_count;

	auto is_formula_valid() const -> bool;
	auto is_operator(char c) const -> bool;
	auto power2n(int n) const -> int;
	auto count_variables() const -> int;

	auto fill_table() -> void;
	auto fill_column(Iter start, Iter end, int step, int filler) -> void;

	auto create_formula(int row_index) const -> std::string;

	auto print_header() const -> void;
	auto print_rows() const -> void;

public:
	TruthTable(const std::string& s);
	auto is_formula_valid(const std::string& formula) const -> bool;
	auto print() const -> void;
};
