#include "adder.hpp"
#include <limits>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("adder", "[adder]")
{

	SECTION("0 + 0")
	{
		uint32_t a = 0;
		uint32_t b = 0;
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}

	SECTION("2 + 2")
	{
		uint32_t a = 2;
		uint32_t b = 2;
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}

	SECTION("0 + 3")
	{
		uint32_t a = 0;
		uint32_t b = 3;
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}

	SECTION("1000 + 234")
	{
		uint32_t a = 1000;
		uint32_t b = 234;
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}

	SECTION("1 + unint32_t::max()")
	{
		uint32_t a = 1;
		uint32_t b = std::numeric_limits<uint32_t>::max();
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}

	SECTION("big + big")
	{
		uint32_t a =    81'029'109;
		uint32_t b = 1'048'103'072;
		uint32_t r = adder(a, b);
		REQUIRE((a + b) == r);
	}
}
