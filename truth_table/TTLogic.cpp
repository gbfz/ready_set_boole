#include "TT.hpp"

void TT::generateTable()
{
	vars = getFormulaVariables();
	colCount = vars.size();
	rowCount = power2N(colCount);
	fillTable();
	addResults();
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
}

void TT::addResults()
{
	for (auto row = 0u; row < rowCount; ++row)
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
		if (std::isalpha(c) && !vars.contains(c))
			vars.emplace(c);
	return std::string(vars.begin(), vars.end());
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
	for (auto i = 0u; i < vars.size(); ++i)
		print("|---");
	print("|---|\n");
}

void TT::printTableRows(auto&& print) const
{
	for (auto row = 0u; row < rowCount; ++row)
	{
		for (char c : vars)
			print("| ", table.at({c, row}), ' ');
		print("| ", table.at({'=', row}), " |\n");
	}
}
