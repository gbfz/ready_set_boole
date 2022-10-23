#include "TT.hpp"

// www.emathhelp.net/calculators/discrete-mathematics/truth-table-calculator

int main()
{
	// std::string s = "AB|";
	std::string s = "AB&C|";
	TT tt;
	tt.setFormula(s);
	tt.generateTable();
	tt.printTable();
}
