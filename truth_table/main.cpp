#include "TruthTable.hpp"
#include <exception>
#include <optional>

auto print_truth_table(const std::string& s) -> void
{
	try {
		TruthTable table(s);
		table.print();
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

// www.emathhelp.net/calculators/discrete-mathematics/truth-table-calculator

auto test(const std::string& s, const std::optional<std::vector<int>>& expected) -> void
{
	try {
		TruthTable table(s);
		if (expected)
		{
			table.print();
			std::cout << std::endl;
			if (table.get_results() != expected)
				std::cerr << "Incorrect results!\n";
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

auto main() -> int
{
	// test("A", {{1,0}});
	// test("O!",			{{0,1}});
	// test("XY|",			{{1,1,1,0}});
	// test("AB=O^B!|A>",	{{1,1,1,1,0,1,0,0}});
	// test("AB&C|",		{{1,1,1,0,1,0,1,0}});
	// test("AB^D&",		{{0,0,1,0,1,0,0,0}});
	// test("AB^D&A=",		{{0,0,1,0,0,1,1,1}});
	// test("AB^D&A=E>",	{{1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0}});
	// test("A!B^D&A=E>",	{{1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0}});
	// test("AB^C^D&A=B>",	{{1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0}});
	// test("AB=C=D|",		{{1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0}});
	// test("AEB=C=D|",	{});
	// test("AAA!!!!!",	{});
	// test("ab|", {});
	// test("||", {});
	// test("=", {});
	// test("AB^C^D&A=B>O", {});
}
