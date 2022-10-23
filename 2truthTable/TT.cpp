#include "TT.hpp"

// get variables
// fill umap<pair<int>, int>
// ??
// profit

std::string TT::getVariablesInitial() const
{
	std::set<char> vars;
	for (char c : formula)
		if (std::isalpha(c) && !vars.contains(c))
			vars.emplace(c);
	return std::string(vars.begin(), vars.end());
}

size_t TT::power2N(size_t n)
{
	size_t pwr = 2;
	for (auto _2 = pwr; --n > 0;)
		pwr *= _2;
	return pwr;
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

void TT::addResults()
{
	for (auto row = 0u; row < rowCount; ++row)
	{
		auto fml = createFormula(row);
		auto tree = ast::generateTree(fml);
		table[{'=', row}] = tree->exec();
	}
}

void TT::fillTable(size_t col, int step, int fill)
{
	if (col == colCount)
		return;
	for (auto row = 0u; row < rowCount; ++row)
	{
		if (row % step == 0)
			fill = !fill;
		table[{vars[col], row}] = fill;
	}
	fillTable(col + 1, step / 2, fill);
}

void TT::generateTable()
{
	vars = getVariablesInitial();
	colCount = vars.size();
	rowCount = power2N(colCount);
	bool fill = false;
	for (size_t step = rowCount / 2; char c : vars)
	{
		for (auto row = 0u; row < rowCount; ++row)
		{
			if (row % step == 0)
				fill = !fill;
			table[{c, row}] = fill;
		}
		step /= 2;
	}
	// fillTable(0, rowCount / 2, false);
	addResults();
}

const TT::tableT& TT::getTable() const
{
	return table;
}

bool TT::operator[](std::pair<char, int> p) const
{
	return table.at(p);
}

void TT::printTableHeader() const
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
	};
	for (char v : vars)
		p("| ", v, ' ');
	p("| = |\n");
	for (auto i = 0u; i < vars.size(); ++i)
		p("|---");
	p("|---|\n");
}

void TT::printTableRows() const
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
	};
	for (auto row = 0u; row < rowCount; ++row)
	{
		for (char c : vars)
			p("| ", table.at({c, row}), ' ');
		p("| ", table.at({'=', row}), " |\n");
	}
}

void TT::printTable() const
{
	printTableHeader();
	printTableRows();
}

void TT::setFormula(const std::string& s)
{
	formula = s;
}

int main()
{
	// std::string s = "AB|";
	std::string s = "AB|C|D=";
	// std::string s = "AB|C=";
	TT tt;
	tt.setFormula(s);
	tt.generateTable();
	tt.printTable();
}
