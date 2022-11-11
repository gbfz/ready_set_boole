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

template <class T>
void p(T cont)
{
	if constexpr ( std::is_same_v<T, std::vector<char>>
				|| std::is_same_v<T, std::set<char>>
				|| std::is_same_v<T, std::deque<char>>)
	{
		std::cout << "{ ";
		for (char c : cont)
			std::cout << c << ' ';
		std::cout << '}';
	}
	if constexpr ( std::is_same_v<T, std::vector<int>>
				|| std::is_same_v<T, std::deque<int>>
				|| std::is_same_v<T, set>)
	{
		std::cout << "{ ";
		for (int i : cont)
			std::cout << i << ' ';
		std::cout << '}';
	}
	if constexpr ( std::is_same_v<T, std::vector<std::vector<int>>>
				|| std::is_same_v<T, std::deque<set>>
				|| std::is_same_v<T, std::vector<set>>)
	{
		std::cout << "{ ";
		for (const auto& v : cont)
		{
			std::cout << "{ ";
			for (int i : v)
				std::cout << i << ' ';
			std::cout << "} ";
		}
		std::cout << '}';
	}
	if constexpr (std::is_same_v<T, std::unordered_map<char, set>>)
	{
		for (const auto& [v, s] : cont)
		{
			std::cout << v << ": { ";
			for (int i : s)
				std::cout << i << ' ';
			std::cout << "}\n";
		}
	}
	std::cout << '\n';
}

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

set& eval(std::deque<set>& s, char c)
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
		case '=': if (a == b)
					  return s.emplace_front(a);
				  s.push_front({});
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
		// return std::cerr << "Invalid formula: " << f << '\n', std::vector<int>();
	// f = nnf::negation_normal_form(f);
	auto vars = getVariables(f);
	if (vars.size() != sets.size())
		return std::cerr << "Number of variables does not match number of sets\n", std::vector<int>();
	U = buildUniverse(sets);

	auto v = assignVariables(vars, sets);
	std::deque<set> d;
	for (char c : f)
	{
		if (std::isalpha(c))
			d.emplace_back(v.at(c));
		else if (is_operator(c))
			eval(d, c);
	}
	/*
	auto makeStack = [v = assignVariables(vars, sets)](auto&& acc, char c)
	{
		if (std::isalpha(c))
			acc.emplace_back(v.at(c));
		return acc;
	};
	auto stack = std::accumulate(f.cbegin(), f.cend(), std::deque<set>(), makeStack);

	auto eval_operators = [&stack](char c)
	{
		if (is_operator(c))
			eval(stack, c);
	};
	std::for_each(f.cbegin(), f.cend(), eval_operators);

	auto collect = [](auto&& acc, const set& s)
	{
		for (int i : s)
			acc.emplace_back(i);
		return acc;
	};
	return std::accumulate(stack.cbegin(), stack.cend(), std::vector<int>(), collect);
	*/
	auto collect = [](auto&& acc, const set& s)
	{
		for (int i : s)
			acc.emplace_back(i);
		return acc;
	};
	return std::accumulate(d.cbegin(), d.cend(), std::vector<int>(), collect);
}

void test(const std::string& s, const std::vector<std::vector<int>>& sets, const std::vector<int>& e)
{
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
