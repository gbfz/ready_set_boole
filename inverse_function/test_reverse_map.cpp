#include "reverse_map.hpp"

#include "libmorton/morton.h"
#include <catch2/catch_test_macros.hpp>

std::pair<uint16_t, uint16_t> libmorton_reverse_map(double n)
{
	constexpr double max = std::numeric_limits<uint32_t>::max();
	uint_fast16_t x, y;
	libmorton::morton2D_32_decode(n * max, x, y);
	return {x, y};
}

TEST_CASE("inverse_function", "[reverse_map]")
{
	SECTION("0")
	{
		double n = 0;
		REQUIRE(reverse_map(n) == libmorton_reverse_map(n));
	}

	SECTION("0.0000022")
	{
		double n = 0.0000022;
		REQUIRE(reverse_map(n) == libmorton_reverse_map(n));
	}

	SECTION("0.345")
	{
		double n = 0.345;
		REQUIRE(reverse_map(n) == libmorton_reverse_map(n));
	}

	SECTION("0.9909")
	{
		double n = 0.9909;
		REQUIRE(reverse_map(n) == libmorton_reverse_map(n));
	}
}
