#include "eval_set.hpp"

namespace SE {

namespace {

namespace rng = std::ranges;

bool is_operator(char c)
{
	return c == '&' || c == '|' || c == '^'
		|| c == '>' || c == '=' || c == '!';
}

set operator& (const set& a, const set& b)
{
	set s;
	rng::set_intersection(a, b, std::inserter(s, s.end()));
	return s;
}

set operator| (const set& a, const set& b)
{
	set s;
	rng::set_union(a, b, std::inserter(s, s.end()));
	return s;
}

set operator^ (const set& a, const set& b)
{
	set s;
	rng::set_symmetric_difference(a, b, std::inserter(s, s.end()));
	return s;
}

const set& process_operator(const set& U, std::deque<set>& s, char c)
{
	const auto neg = [&U](const set& a) -> set {
		if (!a.empty())
			return {};
		set s;
		rng::set_difference(U, a, std::inserter(s, s.end()));
		return s;
	};
	if (c == '!')
		return s.front() = neg(s.front());
	const auto a = s.front(); s.pop_front();
	const auto b = s.front(); s.pop_front();
	switch (c)
	{
		case '&': return s.emplace_front(a & b);
		case '|': return s.emplace_front(a | b);
		case '^': return s.emplace_front(a ^ b);
		case '>': return s.emplace_front(neg(a) | b);
		case '=': return s.emplace_front((a & b) | (neg(a) & neg(b)));
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
	const auto acc = [](auto&& acc, const auto& vec) {
		acc.insert(vec.begin(), vec.end());
		return acc;
	};
	return std::accumulate(sets.begin(), sets.end(), set(), acc);
}

std::unordered_map<char, set> assignVariables(const std::set<char>& vars,
											  const std::vector<std::vector<int>>& sets)
{
	std::unordered_map<char, set> varMap;
	const auto tfm = [](char var, const auto& rng) {
		return std::make_pair(var, set(rng.begin(), rng.end()));
	};
	rng::transform(vars, sets, std::inserter(varMap, varMap.end()), tfm);
	return varMap;
}

std::vector<int> eval_set(const std::string& f,
						  const std::vector<std::vector<int>>& sets,
						  const std::set<char>& vars)
{
	const auto U = buildUniverse(sets);
	const auto varMap = assignVariables(vars, sets);
	const auto acc = [&](auto&& acc, char c)
	{
		if (std::isalpha(c))
			acc.emplace_back(varMap.at(c));
		else if (is_operator(c))
			process_operator(U, acc, c);
		return acc;
	};
	const auto result = std::accumulate(f.begin(), f.end(), std::deque<set>(), acc).front();
	return { result.begin(), result.end() };
}

} // anonymous namespace 

std::vector<int> eval_set(std::string f, const std::vector<std::vector<int>>& sets)
{
	if (!ast::validate(f))
	{
		std::cerr << "Invalid formula: " << f << '\n';
		return {};
	}
	f = nnf::negation_normal_form(f);
	const auto vars = getVariables(f);
	if (vars.size() != sets.size())
	{
		std::cerr << "Number of variables does not match number of sets\n";
		return {};
	}
	return eval_set(f, sets, vars);
}

} // namespace SE
