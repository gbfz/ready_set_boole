#include "eval_set.hpp"

#include "CNForm.hpp"

#include <set>
#include <deque>
#include <unordered_map>

#include <algorithm>

namespace {

namespace rng = std::ranges;

bool is_operator(char c)
{
	return c == '&' || c == '|' || c == '^'
		|| c == '>' || c == '=' || c == '!';
}

std::set<int> operator& (std::set<int> const& a, std::set<int> const& b)
{
	std::set<int> s;
	rng::set_intersection(a, b, std::inserter(s, s.end()));
	return s;
}

std::set<int> operator| (std::set<int> const& a, std::set<int> const& b)
{
	std::set<int> s;
	rng::set_union(a, b, std::inserter(s, s.end()));
	return s;
}

std::set<int> operator^ (std::set<int> const& a, std::set<int> const& b)
{
	std::set<int> s;
	rng::set_symmetric_difference(a, b, std::inserter(s, s.end()));
	return s;
}

std::set<char> getVariables(std::string const& s)
{
	std::set<char> vars;
	for (char c : s) {
		if (std::isalpha(c))
			vars.emplace(c);
	}
	return vars;
}

std::set<int> buildUniverse(std::vector<std::vector<int>> const& sets)
{
	std::set<int> out;
	for (auto const& set : sets) {
		out.insert(set.begin(), set.end());
	}
	return out;
}

auto assignVariables(std::set<char> const& vars,
                     std::vector<std::vector<int>> const& sets)
	-> std::unordered_map<char, std::set<int>>
{
	std::unordered_map<char, std::set<int>> varMap;
	auto map_var_to_set = [](char var, auto const& rng) -> std::pair<char, std::set<int>> {
		return { var, { rng.begin(), rng.end() } };
	};
	rng::transform(vars, sets, std::inserter(varMap, varMap.end()), map_var_to_set);
	return varMap;
}

void process_operator(std::deque<std::set<int>>& s, char c, auto&& negate)
{
	if (c == '!') {
		s.front() = negate(s.front());
		return;
	}
	auto a = std::move(s.front()); s.pop_front();
	auto b = std::move(s.front()); s.pop_front();
	std::set<int> out;
	switch (c)
	{
		case '&': out = a & b; break;
		case '|': out = a | b; break;
		case '^': out = a ^ b; break;
		case '>': out = negate(a) | b; break;
		case '=': out = (a & b) | (negate(a) & negate(b)); break;
	}
	s.emplace_front(std::move(out));
}

auto eval_set(std::string const& formula,
              std::vector<std::vector<int>> const& sets,
              std::set<char> const& vars)
	-> std::vector<int> 
{
	auto const universe = buildUniverse(sets);
	auto negate = [&universe](std::set<int> const& s) -> std::set<int>
	{
		if (!s.empty())
			return {};
		std::set<int> out;
		rng::set_difference(universe, s, std::inserter(out, out.end()));
		return out;
	};

	auto const varMap = assignVariables(vars, sets);
	std::deque<std::set<int>> states;
	for (char c : formula)
	{
		if (is_operator(c)) {
			process_operator(states, c, negate);
		} else {
			states.emplace_back(varMap.at(c));
		}
	}
	auto const out { std::move(states.front()) };
	return { out.begin(), out.end() };
}

} // anonymous namespace 

std::vector<int> eval_set(std::string formula, std::vector<std::vector<int>> const& sets)
{
	if (!ast::validate(formula))
	{
		std::cerr << "Invalid formula: " << formula << '\n';
		return {};
	}
	formula = cnf::conjunctive_normal_form(formula);
	const auto vars = getVariables(formula);
	if (vars.size() != sets.size())
	{
		std::cerr << "Number of variables does not match number of sets\n";
		return {};
	}
	return eval_set(formula, sets, vars);
}
