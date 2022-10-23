#include "TT.hpp"

void TT::setFormula(const std::string& s)
{
	formula = s;
}

size_t TT::power2N(size_t n)
{
	if (n == 0)
		return 1;
	size_t pwr = 2;
	while (--n > 0)
		pwr *= 2;
	return pwr;
}

TT::Table TT::getTableCopy()
{
	return table;
}

const TT::Table& TT::getTable() const
{
	return table;
}

const std::string& TT::getFormula() const
{
	return formula;
}

const std::string& TT::getVariables() const
{
	return vars;
}

size_t TT::getColumnCount() const
{
	return colCount;
}

size_t TT::getRowCount() const
{
	return rowCount;
}

bool TT::operator[](std::pair<char, int> p) const
{
	return table.at(p);
}

bool TT::at(std::pair<char, int> p) const
{
	return table.at(p);
}
