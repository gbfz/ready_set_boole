#pragma once
#include "ASTree.hpp"
#include <map>
#include <set>
#include <iostream>

class TT
{
public:
	using tableT = std::map<std::pair<char, int>, int>;
	void generateTable();

	const tableT& getTable() const;

	void printTable() const;

	bool operator[](std::pair<char, int> p) const;

	void setFormula(const std::string& s);
	std::string getFormula() const;

	std::vector<char> getVariables() const;
	size_t getColumnCount() const;
	size_t getRowCount() const;

private:
	std::string		formula;
	tableT			table;
	std::string		vars;
	size_t			colCount;
	size_t			rowCount;

	size_t power2N(size_t n);
	std::string getVariablesInitial() const;
	void fillTable(size_t col, int step, int fill);
	void addResults();
	std::string createFormula(int row) const;

	void printTableHeader() const;
	void printTableRows() const;
};
