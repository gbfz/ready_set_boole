#include "TruthTable.hpp"
#include "RpnEvaluator.hpp"

auto TruthTable::is_formula_valid(const std::string& formula) const -> bool
{
	int size = 0;
	for (char c : formula)
	{
		size += 1 - is_operator(c);
		if (size <= 0)
			return false;
	}
	return size == 1;
}

auto TruthTable::is_formula_valid() const -> bool
{
	return is_formula_valid(formula);
}

TruthTable::TruthTable(const std::string& s)
	: formula(s)
{
	// if (!is_formula_valid(formula))
		// throw std::runtime_error("Invalid formula");
	for (char c : formula)
	{
		if (std::isalpha(c) && !table.contains(c))
				table[c] = {};
	}
	row_count = power2n(table.size());
	for (auto& [header, cells] : table)
		cells.resize(row_count);
	fill_table();
}

auto TruthTable::fill_table() -> void
{
	auto count = row_count;
	for (auto& [header, cells] : table)
		fill_column(cells.begin(), cells.end(), count /= 2, 1);
}

auto TruthTable::fill_column(Iter start, Iter end, int step, int filler) -> void
{
	if (start == end)
		return;
	for (auto i = 0; i++ < step && start != end;)
		*start++ = filler;
	fill_column(start, end, step, !filler);
}

auto TruthTable::create_formula(int row_index) const -> std::string
{
	std::string s;
	for (char c : formula)
	{
		if (table.contains(c))
			s += table.at(c).at(row_index) + '0';
		else s += c;
	}
	return s;
}

auto TruthTable::power2n(int n) const -> int
{
	auto p = 2;
	for (const auto o = p; --n > 0;)
		p *= o;
	return p;
}

auto TruthTable::is_operator(char c) const -> bool
{
	return c == '!' || c == '&' || c == '|'
		|| c == '^' || c == '>' || c == '=';
}

auto TruthTable::count_variables() const -> int
{
	int count = 0;
	for (char c : formula)
		if (std::isalpha(c))
			++count;
	return count;
}

auto TruthTable::print() const -> void
{
	print_header();
	print_rows();
}

auto TruthTable::print_header() const -> void
{
	for (const auto& [header, _] : table)
		std::cout << "| " << header << ' ';
	std::cout << "| = |\n";
	for (auto i = 0; i < table.size(); ++i)
		std::cout << "|---";
	std::cout << "|---|\n";
}

auto TruthTable::print_rows() const -> void
{
	for (auto i = 0; i < row_count; ++i)
	{
		for (const auto& column : table)
			std::cout << "| " << column.second[i] << ' ';
		auto result = RpnEvaluator(create_formula(i)).evaluate();
		std::cout << "| " << result;// << " |\n";
		std::cout << " | " << create_formula(i) << '\n';
	}
}
