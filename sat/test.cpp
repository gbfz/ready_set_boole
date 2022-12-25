#include "sat.hpp"
#include <optional>
#include <cassert>

void test(const std::string& s, std::optional<bool> expected)
{
	bool actual = sat(s);
	if (expected)
	{
		assert(actual == *expected && "Invalid result");
	}
}

int main()
{
	test("AB|", true);
	test("AB&", true);
	test("AA!&", false);
	test("AA^", false);
}
