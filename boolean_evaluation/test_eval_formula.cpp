#include "eval_formula.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("eval_formula", "[eval_formula]")
{

	SECTION("Simple and")
	{
		auto formula = "10&";
		REQUIRE(eval_formula(formula) == false);
	}

	SECTION("Simple or")
	{
		auto formula = "10|";
		REQUIRE(eval_formula(formula) == true);
	}

	SECTION("Simple implication")
	{
		auto formula = "11>";
		REQUIRE(eval_formula(formula) == true);
	}

	SECTION("Simple equality")
	{
		auto formula = "10=";
		REQUIRE(eval_formula(formula) == false);
	}

	SECTION("Compound short 1")
	{
		auto formula = "1011||=";
		REQUIRE(eval_formula(formula) == true);
	}

	SECTION("Compound short 2")
	{
		auto formula = "11|1&1=";
		REQUIRE(eval_formula(formula) == true);
	}

	SECTION("Compound short 2.5:\
			 same as before but operators at end")
	{
		auto formula = "1111|&=";
		REQUIRE(eval_formula(formula) == true);
	}

	SECTION("Compound long 1")
	{
		auto formula = "10^00||0=1&";
		REQUIRE(eval_formula(formula) == false);
	}

}
