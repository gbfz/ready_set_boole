#include "eval_set.hpp"

namespace SE {

namespace {

namespace rng = std::ranges;

bool is_operator(char c)
{
	return c == '&' || c == '|' || c == '^'
		|| c == '>' || c == '=' || c == '!';
}

Set operator& (const Set& a, const Set& b)
{
	Set s;
	rng::set_intersection(a, b, std::inserter(s, s.end()));
	return s;
}

Set operator| (const Set& a, const Set& b)
{
	Set s;
	rng::set_union(a, b, std::inserter(s, s.end()));
	return s;
}

Set operator^ (const Set& a, const Set& b)
{
	Set s;
	rng::set_symmetric_difference(a, b, std::inserter(s, s.end()));
	return s;
}

const Set& process_operator(const Set& U, std::deque<Set>& s, char c)
{
	const auto neg = [&U](const Set& a) -> Set {
		if (!a.empty())
			return {};
		Set s;
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
		if (std::isalpha(c))
			vars.emplace(c);
	return vars;
}

Set buildUniverse(const std::vector<std::vector<int>>& sets)
{
	const auto acc = [](auto&& acc, const auto& vec) {
		acc.insert(vec.begin(), vec.end());
		return acc;
	};
	return std::accumulate(sets.begin(), sets.end(), Set(), acc);
}

std::unordered_map<char, Set> assignVariables(const std::set<char>& vars,
											  const std::vector<std::vector<int>>& sets)
{
	std::unordered_map<char, Set> varMap;
	const auto tfm = [](char var, const auto& rng) {
		return std::make_pair(var, Set(rng.begin(), rng.end()));
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
	const auto acc = [&](auto&& res, char c)
	{
		if (std::isalpha(c))
			res.emplace_back(varMap.at(c));
		else if (is_operator(c))
			process_operator(U, res, c);
		return res;
	};
	const auto result = std::accumulate(f.begin(), f.end(), std::deque<Set>(), acc).front();
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
