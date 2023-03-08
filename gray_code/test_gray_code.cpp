#include "gray_code.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("gray_code", "[gray_code]")
{
	
	SECTION("0")
	{
		REQUIRE(gray_code(0) == 0);
	}

	SECTION("1")
	{
		REQUIRE(gray_code(1) == 1);
	}

	SECTION("2")
	{
		REQUIRE(gray_code(2) == 3);
	}

	SECTION("3")
	{
		REQUIRE(gray_code(3) == 2);
	}

	SECTION("4")
	{
		REQUIRE(gray_code(4) == 6);
	}

	SECTION("5")
	{
		REQUIRE(gray_code(5) == 7);
	}

	SECTION("420")
	{
		REQUIRE(gray_code(420) == 374);
	}

}
