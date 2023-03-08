#include "truth_table.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("truth_table")
{

	TruthTable tt;
	std::vector<int> expected;

	SECTION("X")
	{
		tt.generateTable("X");
		expected = {1, 0};
		REQUIRE(tt.getResults() == expected);
	}

	SECTION("XY^")
	{
		tt.generateTable("XY^");
		expected = {0, 1, 1, 0};
		REQUIRE(tt.getResults() == expected);
	}

	SECTION("AB&C|")
	{
		tt.generateTable("AB&C|");
		expected = {1, 1, 1, 0, 1, 0, 1, 0};
		REQUIRE(tt.getResults() == expected);
	}

}
