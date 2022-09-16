#include "TruthTable.hpp"
#include "RpnEvaluator.hpp"

TruthTable::TruthTable(const std::string& s) : formula(s)
{
	if (!is_formula_valid())
		throw std::runtime_error("Invalid formula");
	for (char c : formula)
		if (std::isalpha(c) && !table.contains(c))
				table[c] = {};
	row_count = power2n(table.size());
	for (auto& [_, column] : table)
		column.resize(row_count);
	fill_table();
}

auto TruthTable::fill_table() -> void
{
	auto count = row_count;
	for (auto& [_, column] : table)
		fill_column(column.begin(), column.end(), count /= 2, 1);
	calculate_results();
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
	s.reserve(formula.length());
	for (char c : formula)
	{
		if (table.contains(c))
			s += table.at(c).at(row_index) + '0';
		else s += c;
	}
	return s;
}

auto TruthTable::calculate_results() -> void
{
	if (!results.empty())
		return;
	results.reserve(row_count);
	for (auto i = 0; i < row_count; ++i)
	{
		auto result = RpnEvaluator(create_formula(i)).evaluate();
		results.push_back(result);
	}
}

auto TruthTable::power2n(int n) const -> int
{
	auto p = 2;
	for (const auto o = p; --n > 0;)
		p *= o;
	return p;
}

auto TruthTable::count_variables() const -> int
{
	auto count = 0;
	for (char c : formula)
		if (std::isalpha(c))
			++count;
	return count;
}

auto TruthTable::print() const -> void
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
	};
	for (const auto& [header, _] : table)
		p("| ", header, ' ');
	p("| = |\n");
	for (auto i = 0; i < table.size(); ++i)
		p("|---");
	p("|---|\n");
	for (auto i = 0; i < row_count; ++i)
	{
		for (const auto& [_, column] : table)
			p("| ", column[i], ' ');
		p("| ", results[i], " |\n");
	}
}

auto TruthTable::get_results() const -> std::vector<int>
{
	return results;
}

auto TruthTable::is_formula_valid() const -> bool
{
	auto size = 0;
	auto valence = 0;
	for (char c : formula)
	{
		switch (c)
		{
			case '&': case '|': case '^': case '>': case '=':
				valence = 2; break;
			case '!':
				valence = 1; break;
			default:
				if (!(std::isalpha(c) && std::isupper(c)))
					return false;
				valence = 0; break;
		}
		size += 1 - valence;
	}
	return size == 1;
}
