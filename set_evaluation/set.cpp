#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <iostream>
// #include "../negation_normal_form/NNForm.hpp"

using set = std::set<int>;

set U;

set operator& (const set& a, const set& b)
{
	set s;
	std::ranges::set_intersection(a, b, std::inserter(s, s.end()));
	return s;
}

set operator| (const set& a, const set& b)
{
	set s;
	std::ranges::set_union(a, b, std::inserter(s, s.end()));
	return s;
}

set operator^ (const set& a, const set& b)
{
	set s;
	std::ranges::set_symmetric_difference(a, b, std::inserter(s, s.end()));
	return s;
}

set operator! (const set& a)
{
	if (!a.empty())
		return {};
	set s;
	std::ranges::set_difference(U, a, std::inserter(s, s.end()));
	return s;
}

const set& process_operator(std::deque<set>& s, char c)
{
	if (c == '!')
		return s.front() = !s.front();
	auto a = s.front(); s.pop_front();
	auto b = s.front(); s.pop_front();
	switch (c)
	{
		case '&': return s.emplace_front(a & b);
		case '|': return s.emplace_front(a | b);
		case '^': return s.emplace_front(a ^ b);
		case '>': return s.emplace_front(!a | b);
		case '=': return s.emplace_front((a & b) | (!a & !b));
	}
	return U;
}

std::set<char> getVariables(const std::string& s)
{
	std::set<char> vars;
	for (char c : s)
	{
		if (std::isalpha(c))
			vars.emplace(c);
	}
	return vars;
}

set buildUniverse(const std::vector<std::vector<int>>& sets)
{
	auto acc = [](auto&& acc, const std::vector<int>& vec) {
		acc.insert(vec.begin(), vec.end());
		return acc;
	};
	return std::accumulate(sets.begin(), sets.end(), set(), acc);
}

std::unordered_map<char, set> assignVariables(const std::set<char>& vars,
											  const std::vector<std::vector<int>>& sets)
{
	std::unordered_map<char, set> m;
	auto tfm = [](char var, const std::vector<int>& rng) {
		return std::make_pair(var, set(rng.begin(), rng.end()));
	};
	std::ranges::transform(vars, sets, std::inserter(m, m.begin()), tfm);
	return m;
}

bool is_operator(char c)
{
	return c == '&' || c == '|' || c == '^'
		|| c == '>' || c == '=' || c == '!';
}

std::vector<int> eval_set(std::string f, const std::vector<std::vector<int>>& sets)
{
	// if (!ast::validate(f))
	// {
		// std::cerr << "Invalid formula: " << f << '\n';
		// return {};
	// }
	// f = nnf::negation_normal_form(f);
	auto vars = getVariables(f);
	if (vars.size() != sets.size())
	{
		std::cerr << "Number of variables does not match number of sets\n";
		return {};
	}

	U = buildUniverse(sets);

	auto acc = [v = assignVariables(vars, sets)](auto&& acc, char c) {
		if (std::isalpha(c))
			acc.emplace_back(v.at(c));
		else if (is_operator(c))
			process_operator(acc, c);
		return acc;
	};
	auto result = std::accumulate(f.cbegin(), f.cend(), std::deque<set>(), acc).front();

	return { result.begin(), result.end() };
}

void test(const std::string& s, const std::vector<std::vector<int>>& sets, const std::vector<int>& e)
{
	auto p = [](const std::vector<int>& v) {
		std::cout << "{ ";
		for (int i : v)
			std::cout << i << ' ';
		std::cout << "}\n";
	};
	auto r = eval_set(s, sets);
	if (r != e)
	{
		std::cerr << "Invalid result with " << s << '\n';
		std::cerr << "Expected: ";
		p(e);
		std::cerr << "Actual:   ";
		p(r);
	}
	else std::cerr << s << " oк\n";
}

int main()
{
	test("A!", {{0, 1, 2}}, {});
	test("AB&", {{0, 1, 2}, {0, 3, 4}}, {0});
	test("AB&", {{}, {}}, {});
	test("AB|", {{0, 1, 2}, {3, 4, 5}}, {0, 1, 2, 3, 4, 5});
	test("AB&A^", {{0, 1, 2}, {3, 4, 5}}, {0, 1, 2});
	test("AB|A^", {{0, 1, 2}, {3, 4, 5}}, {3, 4, 5});
	test("AB|C=", {{0}, {1, 2}, {0, 1, 2}}, {0, 1, 2});
	test("AB=", {{}, {1}}, {});
	test("ABA^^", {{0, 1, 2}, {3, 4, 5}}, {3, 4, 5});
}
