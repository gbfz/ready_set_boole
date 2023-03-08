#include "sat.hpp"
#include "truth_table.hpp"

#include <iostream>

bool sat(const std::string& s)
{
	TruthTable tt;
	if (!tt.generateTable(s))
	{
		std::cerr << "Invalid formula: " << s << '\n';
		return false;
	}
	for (size_t row : tt.getResults()) {
		if (tt.at({'=', row})) {
			return true;
		}
	}
	return false;
}
