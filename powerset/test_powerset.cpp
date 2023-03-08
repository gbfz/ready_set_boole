#include "powerset.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

TEST_CASE("powerset", "[powerset]")
{

	using Catch::Matchers::UnorderedEquals;

	SECTION("a, b, c")
	{
		auto pset = powerset({'a', 'b', 'c'});
		decltype(pset) expected = {
			{'a'}, {'a', 'b'}, {'a', 'c'}, {'a', 'b', 'c'},
			{'b'}, {'b', 'c'},
			{'c'},
			{}
		};
		REQUIRE_THAT(pset, UnorderedEquals(expected));
	}

	SECTION("a, a, c")
	{
		auto pset = powerset({'a', 'a', 'c'});
		decltype(pset) expected = {
			{'a'}, {'a', 'a'}, {'a', 'c'}, {'a', 'a', 'c'},
			{'a'}, {'a', 'c'},
			{'c'},
			{ }
		};
		REQUIRE_THAT(pset, UnorderedEquals(expected));
	}

	SECTION("1")
	{
		auto pset = powerset({1});
		decltype(pset) expected = {
			{1},
			{ }
		};
		REQUIRE_THAT(pset, UnorderedEquals(expected));
	}

	SECTION("empty")
	{
		auto pset = powerset({});
		decltype(pset) expected = {
			{ }
		};
		REQUIRE(pset == expected);
	}

	SECTION("long...")
	{
		auto pset = powerset({3, 14, 15, 92, 6});
		decltype(pset) expected = {
			{}, {3}, {14}, {3, 14},
			{15}, {3, 15}, {14, 15},
			{3, 14, 15}, {92}, {3, 92},
			{14, 92}, {3, 14, 92},
			{15, 92}, {3, 15, 92},
			{14, 15, 92}, {3, 14, 15, 92},
			{6}, {3, 6}, {14, 6}, {3, 14, 6},
			{15, 6}, {3, 15, 6}, {14, 15, 6},
			{3, 14, 15, 6}, {92, 6},
			{3, 92, 6}, {14, 92, 6},
			{3, 14, 92, 6}, {15, 92, 6},
			{3, 15, 92, 6}, {14, 15, 92, 6},
			{3, 14, 15, 92, 6}
		};
		REQUIRE_THAT(pset, UnorderedEquals(expected));
	}

}
