#include "eval_set.hpp"

void test(const std::string& s, const std::vector<std::vector<int>>& sets, const std::vector<int>& e)
{
	auto print = [](const std::vector<int>& v) {
		std::cout << "{ ";
		for (int i : v)
			std::cout << i << ' ';
		std::cout << "}\n";
	};
	auto r = SE::eval_set(s, sets);
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
	test("A!",    {{0, 1, 2}}, 				{});
	test("A!!!!", {{8}},					{8});
	test("AB&",   {{0, 1, 2}, {0, 3, 4}},	{0});
	test("AB&",   {{}, {}},					{});
	test("A!A&",  {{1}},					{});
	test("AB|",   {{0, 1, 2}, {3, 4, 5}},	{0, 1, 2, 3, 4, 5});
	test("AB&A^", {{0, 1, 2}, {3, 4, 5}},	{0, 1, 2});
	test("AB|A^", {{0, 1, 2}, {3, 4, 5}},	{3, 4, 5});
	test("AB|C=", {{0}, {1, 2}, {0, 1, 2}}, {0, 1, 2});
	test("AB=",   {{}, {1}},				{});
	test("ABA^^", {{0, 1, 2}, {3, 4, 5}},	{3, 4, 5});
}
