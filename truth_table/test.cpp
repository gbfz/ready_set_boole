#include "TT.hpp"
#include <iomanip>
#include <iostream>

// www.emathhelp.net/calculators/discrete-mathematics/truth-table-calculator

void test(const std::string& formula, const std::vector<int>& expected)
{
	TT tt;
	if (!tt.generateTable(formula)) {
		std::cerr << "Invalid formula: " << formula << '\n';
		return;
	}
	if (tt.getResults() != expected) {
		std::cerr << "Invalid results, expected:\n";
		for (auto e : expected)
			std::cerr << e << ' ';
		std::cerr << "\nactual:\n";
		for (auto e : tt.getResults())
			std::cerr << e << ' ';
		std::cerr << '\n';
	} else {
		std::cout << "Formula " << std::quoted(formula) << " is ok\n";
		tt.printTable();
		std::cout << '\n';
	}
}

int main()
{
	test("X", {1, 0});
	test("XY^", {0,1,1,0});
	test("AB&C|", {1,1,1,0,1,0,1,0});
	test("AB&CD^|", {1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0});
}
