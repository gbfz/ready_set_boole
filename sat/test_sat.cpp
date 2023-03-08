#include "sat.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("sat", "[sat]")
{

	SECTION("AB|")
	{
		REQUIRE(sat("AB|") == true);
	}

	SECTION("AB&")
	{
		REQUIRE(sat("AB&") == true);
	}

	SECTION("AA!&")
	{
		REQUIRE(sat("AA!&") == false);
	}

	SECTION("AA!&")
	{
		REQUIRE(sat("AA^") == false);
	}

}
