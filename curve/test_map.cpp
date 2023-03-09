#include "map.hpp"
#include "libmorton/morton.h"
#include <catch2/catch_test_macros.hpp>
#include "catch2/catch_approx.hpp"

double libmorton_map(uint16_t x, uint16_t y)
{
	constexpr double max = std::numeric_limits<uint32_t>::max();
	return libmorton::morton2D_32_encode(x, y)
		 / max;
}

TEST_CASE("curve", "[map]")
{

	using Catch::Approx;

	uint16_t x = 0;
	uint16_t y = 0;

	SECTION("0, 0")
	{
		x = 0;
		y = 0;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("16, 42")
	{
		x = 16;
		y = 42;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("100, 100")
	{
		x = 100;
		y = 100;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}


	SECTION("33451, 100")
	{
		x = 33451;
		y = 100;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("33451, 200")
	{
		x = 33451;
		y = 200;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("16000, 16000")
	{
		x = 16000;
		y = 16000;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("42000, 42000")
	{
		x = 42000;
		y = 42000;
		double expected = libmorton_map(x, y);
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

	SECTION("65535, 65535")
	{
		x = 65535;
		y = 65535;
		double expected = libmorton::morton2D_32_encode(x, y);
		expected /= std::numeric_limits<uint32_t>::max();
		double real     = map(x, y);
		REQUIRE(real == Approx(expected));
	}

}
