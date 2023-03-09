#include "eval_set.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

TEST_CASE("eval_set", "[eval_set]")
{
	using Catch::Matchers::UnorderedEquals;
	using data_t = std::vector<std::vector<int>>;

	SECTION("A!") // 1
	{
		auto formula = "A!";
		data_t data = {
			{0, 1, 2}
		};
		std::vector<int> expected {};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("A!!!!") // 2
	{
		auto formula = "A!!!!";
		data_t data = { {8} };
		std::vector<int> expected {8};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB&") // 3
	{
		auto formula = "AB&";
		data_t data = {
			{0, 1, 2},
			{0, 3, 4}
		};
		std::vector<int> expected {0};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB&") // 4
	{
		auto formula = "AB&";
		data_t data = {
			{ },
			{ }
		};
		std::vector<int> expected {};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("A!A&") // 5
	{
		auto formula = "A!A&";
		data_t data = {
			{1},
		};
		std::vector<int> expected {};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB|") // 6
	{
		auto formula = "AB|";
		data_t data = {
			{0, 1, 2},
			{3, 4, 5}
		};
		std::vector<int> expected {0, 1, 2, 3, 4, 5};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB&A^") // 7
	{
		auto formula = "AB&A^";
		data_t data = {
			{0, 1, 2},
			{3, 4, 5}
		};
		std::vector<int> expected {0, 1, 2};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB|A^") // 8
	{
		auto formula = "AB|A^";
		data_t data = {
			{0, 1, 2},
			{3, 4, 5}
		};
		std::vector<int> expected {3, 4, 5};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB|C=") // 9
	{
		auto formula = "AB|C=";
		data_t data = {
			{0},
			{1, 2},
			{0, 1, 2}
		};
		std::vector<int> expected {0, 1, 2};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("AB=") // 10
	{
		auto formula = "AB=";
		data_t data = {
			{ },
			{1}
		};
		std::vector<int> expected { };

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}

	SECTION("ABA^^") // 11
	{
		auto formula = "ABA^^";
		data_t data = {
			{0, 1, 2},
			{3, 4, 5}
		};
		std::vector<int> expected {3, 4, 5};

		auto eval = eval_set(formula, data);

		REQUIRE_THAT(eval, UnorderedEquals(expected));
	}
}

/*
void test(const std::string& s, const std::vector<std::vector<int>>& sets, const std::vector<int>& e)
{
	auto print = [](const std::vector<int>& v) {
		std::cout << "{ ";
		for (int i : v)
			std::cout << i << ' ';
		std::cout << "}\n";
	};
	auto r = eval_set(s, sets);
	std::cout << "Formula: " << s << ", sets:\n";
	for (const auto& v : sets)
		print(v);
	std::cout << "Expected: ";
	print(e);
	std::cout << "Actual:   ";
	print(r);
	if (r != e)
	{
		std::cout << "Invalid result" << '\n';
	}
	std::cout << '\n';
}

int main()
{
1	test("A!",    {{0, 1, 2}}, 				{});
2	test("A!!!!", {{8}},					{8});
3	test("AB&",   {{0, 1, 2}, {0, 3, 4}},	{0});
4	test("AB&",   {{}, {}},					{});
5	test("A!A&",  {{1}},					{});
6	test("AB|",   {{0, 1, 2}, {3, 4, 5}},	{0, 1, 2, 3, 4, 5});
7	test("AB&A^", {{0, 1, 2}, {3, 4, 5}},	{0, 1, 2});
8	test("AB|A^", {{0, 1, 2}, {3, 4, 5}},	{3, 4, 5});
9	test("AB|C=", {{0}, {1, 2}, {0, 1, 2}}, {0, 1, 2});
10	test("AB=",   {{}, {1}},				{});
11	test("ABA^^", {{0, 1, 2}, {3, 4, 5}},	{3, 4, 5});
}
*/
