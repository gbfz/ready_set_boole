#include "multiplier.hpp"
#include <limits>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("multiplier", "[multiplier]")
{

	SECTION("0 * 0")
	{
		uint32_t a = 0;
		uint32_t b = 0;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}

	SECTION("0 * 2")
	{
		uint32_t a = 0;
		uint32_t b = 2;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}

	SECTION("2 * 2")
	{
		uint32_t a = 2;
		uint32_t b = 2;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}

	SECTION("1 * 1234")
	{
		uint32_t a = 1;
		uint32_t b = 1234;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}

	SECTION("123 * 456")
	{
		uint32_t a = 123;
		uint32_t b = 456;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}

	SECTION("1'002'305 * 32'020")
	{
		uint32_t a = 1'002'305;
		uint32_t b =    32'020;
		uint32_t r = multiplier(a, b);
		REQUIRE((a * b) == r);
	}
}
