#include <exception>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>

auto eval_formula(const std::string& formula) -> bool;

using Table = std::map<char, std::vector<int>>;

auto COUNT = 0ull;

auto is_operator(char c) -> bool
{
	return c == '!' || c == '&' || c == '|'
		|| c == '^' || c == '>' || c == '=';
}

auto power2n(int n)
{
	unsigned long long p = 2;
	for (const auto o = p; --n > 0;)
		p *= o;
	return p;
}

auto count_variables(const std::string& s) -> std::size_t
{
	return std::count_if(s.begin(), s.end(), [](char c) {
			return std::isalpha(c) && std::isupper(c);
	});
}

auto create_table(const std::string& s) -> Table
{
	Table table;
	auto variable_count = count_variables(s);
	for (char c : s)
	{
		if (std::isalpha(c) && std::isupper(c))
		{
			if (!table.contains(c))
				table[c].resize(power2n(variable_count));
		}
		else if (!is_operator(c))
			throw std::exception();
	}
	return table;
}

template <class Iter>
auto fill_column(Iter start, Iter end, size_t step, int filler) -> void
{
	auto i = 0ul;
	while (i++ < step && start != end)
		*start++ = filler;
	if (start != end)
		fill_column(start, end, step, !filler);
}

auto fill_table(Table& table, const std::string& s) -> Table&
{
	auto count = power2n(count_variables(s)); // TODO: maybe use a class and store this upon its construction?
	COUNT = count;
	for (auto& column : table)
	{
		auto& cells = column.second;
		fill_column(cells.begin(), cells.end(), count /= 2, 1);
	}
	return table;
}

auto create_formula(const auto& table, size_t row_index, const std::string& original) -> std::string
{
	std::string formula;
	for (char c : original)
	{
		if (table.contains(c))
			formula += table.at(c).at(row_index) + '0';
		else formula += c;
	}
	return formula;
}

auto print_header(const Table& table) -> void
{
	for (const auto& column : table)
		std::cout << "| " << column.first << ' ';
	std::cout << "| = |\n";
	for (auto i = 0; i < table.size(); ++i)
		std::cout << "|---";
	std::cout << "|---|\n";
}

auto print_table(const Table& table, const std::string& f) -> void
{
	print_header(table);
	for (auto i = 0ull; i < COUNT; ++i)
	{
		for (const auto& column : table)
			std::cout << "| " << column.second[i] << ' ';
		std::cout << "| " << eval_formula(create_formula(table, i, f)) << "|\n";
	}
}

auto main() -> int
{
	auto f = "AB&C|";
	auto table = create_table(f);
	table = fill_table(table, f);
	print_table(table, f);
}
