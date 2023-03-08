#pragma once

#include <string>
#include <vector>
#include <map>

class TruthTable
{
public:
	using Table = std::map<std::pair<char, int>, int>;

	bool generateTable(const std::string& formula);
	void printTable() const;

	std::vector<int> getResults() const;
	bool at(std::pair<char, int> p) const;

private:
	std::string		formula;
	Table			table;
	std::string		vars;
	size_t			colCount;
	size_t			rowCount;

	size_t power2N(size_t n);
	std::string getFormulaVariables() const;
	void fillTable();
	void addResults();
	std::string createFormula(int row) const;

	void printTableHeader(auto&& print) const;
	void printTableRows(auto&& print) const;
};
