#include "ASTree.hpp"
#include "NNForm.hpp"
#include <catch2/catch_test_macros.hpp>

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	A!B|AB!|&
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 */

TEST_CASE("negation_normal_form", "[negation_normal_form]")
{
	SECTION("Double negation")
	{
		auto formula = "A!!";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A");
	}

	SECTION("Quadruple negation")
	{
		auto formula = "A!!!!";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A");
	}

	SECTION("Implication")
	{
		auto formula = "AB>";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A!B|");
	}

	SECTION("Equivalence")
	{
		auto formula = "AB=";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A!B|AB!|&");
	}

	SECTION("De Morgan's I")
	{
		auto formula = "AB|!";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A!B!&");
	}

	SECTION("De Morgan's II")
	{
		auto formula = "AB&!";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "A!B!|");
	}

	SECTION("Wrong formula")
	{
		auto formula = "=D";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "");
	}

	SECTION("Empty")
	{
		auto formula = "";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "");
	}

	SECTION("Complex")
	{
		auto formula = "AB|C&D=X>";
		auto norm = nnf::negation_normal_form(formula);

		REQUIRE(norm == "AB|C&D!&A!B!&C!|D&|X|");
	}
}
