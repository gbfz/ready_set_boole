#include "sat.hpp"

bool sat(const std::string& s)
{
	TT tt;
	if (!tt.setFormula(s))
	{
		std::cerr << "Invalid formula: " << s << '\n';
		return false;
	}
	tt.generateTable();
	const auto& table = tt.getTable();
	for (size_t row = 0; row < tt.getRowCount(); ++row)
		if (table.at({'=', row}) == true)
			return true;
	return false;
}
