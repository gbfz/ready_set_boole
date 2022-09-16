#include "TruthTable.hpp"

auto test(const std::string& s) -> void
{
	TruthTable table(s);
	table.print();
	std::cout << std::endl;
}

auto main() -> int
{
	// test("AB&C|");
	// test("AB^D&");
	// test("AB^D&A=");
	// test("AB^D&A=E>");
	// test("A!B^D&A=E>");
	// test("AB^C^D&A=B>");
	test("AB=C=D|");
}
