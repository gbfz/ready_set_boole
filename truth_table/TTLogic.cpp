#include "TT.hpp"
#include <set>
#include <iostream>

bool TT::generateTable(const std::string& f)
{
	if (!ast::validate(f))
		return false;
	formula = f;
	vars = getFormulaVariables();
	colCount = vars.size();
	rowCount = power2N(colCount);
	fillTable();
	return true;
}

void TT::fillTable()
{
	bool fill = false;
	size_t step = rowCount / 2;
	for (char col : vars)
	{
		for (size_t row = 0; row < rowCount; ++row)
		{
			if (row % step == 0)
				fill = !fill;
			table[{col, row}] = fill;
		}
		step /= 2;
	}
	addResults();
}

void TT::addResults()
{
	for (size_t row = 0; row < rowCount; ++row)
	{
		auto fml = createFormula(row);
		auto tree = ast::generateTree(fml);
		table[{'=', row}] = tree->exec();
	}
}

std::string TT::createFormula(int row) const
{
	std::string s;
	s.reserve(formula.size());
	for (char c : formula)
	{
		if (std::isalpha(c))
			s += table.at({c, row}) + '0';
		else s += c;
	}
	return s;
}

std::string TT::getFormulaVariables() const
{
	std::set<char> vars;
	for (char c : formula)
		if (std::isalpha(c))
			vars.emplace(c);
	return std::string(vars.begin(), vars.end());
}

size_t TT::power2N(size_t n)
{
	if (n == 0)
		return 1;
	return 2 << (n - 1);
}

std::vector<int> TT::getResults() const
{
	std::vector<int> rs;
	for (size_t row = 0; row < rowCount; ++row)
		rs.emplace_back(table.at({'=', row}));
	return rs;
}

bool TT::at(std::pair<char, int> p) const
{
	return table.at(p);
}

void TT::printTable() const
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
	};
	printTableHeader(p);
	printTableRows(p);
}

void TT::printTableHeader(auto&& print) const
{
	for (char v : vars)
		print("| ", v, ' ');
	print("| = |\n");
	for (size_t i = 0; i < vars.size(); ++i)
		print("|---");
	print("|---|\n");
}

void TT::printTableRows(auto&& print) const
{
	for (size_t row = 0; row < rowCount; ++row)
	{
		for (char c : vars)
			print("| ", table.at({c, row}), ' ');
		print("| ", table.at({'=', row}), " |\n");
	}
}
