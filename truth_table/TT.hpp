#pragma once
#include "ASTree.hpp"
#include <map>
#include <set>
#include <iostream>

class TT
{
public:
	using Table = std::map<std::pair<char, int>, int>;

	void generateTable();

	void setFormula(const std::string& s);

	bool operator[](std::pair<char, int> p) const;
	bool at(std::pair<char, int> p) const;

	void printTable() const;

	Table getTableCopy();
	const Table& getTable() const;
	const std::string& getFormula() const;
	const std::string& getVariables() const;
	size_t getColumnCount() const;
	size_t getRowCount() const;

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
