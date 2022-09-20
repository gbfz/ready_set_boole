#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <map>
#include <optional>
#include <ranges>
#include <regex>
#include <functional>

#include <cassert>

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	AB&A!B!&|
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 * Distributivity I:	AB|C&	≡	CA&CB&|
 * Distributivity II:	AB&C|	≡	CA|CB|&
 */

using SimplTable = std::unordered_map<char, std::string>;

enum class Pattern
{
	DoubleNegation,
	Implication,
	Equivalence,
	DeMorgans1,
	DeMorgans2,
};

auto p = [](auto&&... args) {
	((std::cout << std::boolalpha << args), ...);
	std::cout << '\n';
};

auto pp(Pattern pt)
{
	switch (pt)
	{
		case Pattern::DoubleNegation: p("Double negation"); break;
		case Pattern::Implication: p("Implication"); break;
		case Pattern::Equivalence: p("Equivalence"); break;
		case Pattern::DeMorgans1: p("DeMorgans1"); break;
		case Pattern::DeMorgans2: p("DeMorgans2"); break;
	}
}

auto is_operator(char c) -> bool
{
	return c == '!' || c == '&' || c == '|'
		|| c == '>' || c == '=';
}

auto is_variable(char c) -> bool
{
	return std::isupper(c) && !is_operator(c);
}

auto is_single_binary_operation(const std::string& s, auto i) -> bool
{
	return is_variable(s[i - 2])
		&& is_variable(s[i - 1])
		&& !is_operator(s[i + 1]);
};

auto is_normal_form(const std::string& s) -> bool
{
	static const std::regex exp("!!|\\|!|&!|>|=");
	return !std::regex_search(s, exp);
}

static const std::unordered_map<std::string, Pattern> original =
{
	{"!!",	Pattern::DoubleNegation},
	{">",	Pattern::Implication},
	{"=",	Pattern::Equivalence},
	{"|!",	Pattern::DeMorgans1},
	{"&!",	Pattern::DeMorgans2},
	// {"|&",	Pattern::Distr1},
	// {"&|",	Pattern::Distr2},
};

auto rewrite_double_negation(std::string& s)
{
	auto pos = s.rfind("!!");
	auto replacement = {s[pos - 1]};
	s.replace(pos - 1, 2, replacement);
}

auto rewrite_implication(std::string& s)
{
	auto pos = s.rfind(">");
	auto a = s[pos - 2];
	auto b = s[pos - 1];
	auto replacement = {a, '!', b, '|'};
	s.replace(pos - 2, 3, replacement);
}

auto rewrite_equivalence(std::string& s)
{
	auto pos = s.rfind("=");
	auto a = s[pos - 2];
	auto b = s[pos - 1];
	auto replacement = {a, b, '&', a, '!', b, '!', '&', '|'};
	s.replace(pos - 2, 3, replacement);
}

auto rewrite_deMorgans1(std::string& s)
{
	auto pos = s.rfind("|!");
	auto a = s[pos - 2];
	auto b = s[pos - 1];
	auto replacement = {a, '!', b, '!', '|'};
	s.replace(pos - 2, 4, replacement);
}

auto rewrite_deMorgans2(std::string& s)
{
	auto pos = s.rfind("&!");
	auto a = s[pos - 2];
	auto b = s[pos - 1];
	auto replacement = {a, '!', b, '!', '&'};
	s.replace(pos - 2, 4, replacement);
}

static const std::unordered_map<Pattern, std::function<void(std::string&)>> rewriters =
{
	{Pattern::DoubleNegation,	rewrite_double_negation},
	{Pattern::Implication,		rewrite_implication},
	{Pattern::Equivalence,		rewrite_equivalence},
	{Pattern::DeMorgans1,		rewrite_deMorgans1},
	{Pattern::DeMorgans2,		rewrite_deMorgans2},
};

auto rewrite(std::string& s, Pattern pattern)
{
	return rewriters.at(pattern)(s);
}

auto match_op(const std::string& s) -> size_t
{
	auto i = s.find_last_of("|&!>=");
	if (i == std::string::npos)
		return i;
	if (is_single_binary_operation(s, i))
		return i - 2;
	return std::string::npos;
}

auto simplify(std::string& s, SimplTable& m, char sub) -> void
{
	auto pos = match_op(s);
	if (pos == std::string::npos)
		return;
	m.insert({sub, s.substr(pos, 3)});
	s.replace(pos, 3, {sub});
	return simplify(s, m, sub + 1);
}

auto reinstate(std::string& s, SimplTable& m, size_t i) -> void
{
	if (i >= s.size())
		return;
	if (m.contains(s[i]))
	{
		s.replace(i, 1, m.at(s[i]));
		m.erase(s[i]);
	}
	reinstate(s, m, i + 1);
}

auto match_pattern(const std::string& s) -> Pattern
{
	static const std::regex exp("!!|\\|\\!|\\&\\!|>|=");
	std::smatch matched_str;
	if (std::regex_search(s, matched_str, exp))
		return original.at(matched_str.str());
	throw std::runtime_error("Fuck");
}

auto negation_normal_form(std::string s) -> std::string
{
	SimplTable simplified_tokens_map;
	while (!is_normal_form(s))
	{
		simplify(s, simplified_tokens_map, 'a');
		// pp(match_pattern(s));
		rewrite(s, match_pattern(s));
		reinstate(s, simplified_tokens_map, 0);
	}
	return s;
}

auto testSimRei(std::string s)
{
	SimplTable m;
	simplify(s, m, 'a');
	p(s);
	reinstate(s, m, 0);
	p(s);
}

auto testForm(const std::string& s)
{
	p(negation_normal_form(s));
}

auto main() -> int
{
	// testForm("AB&!"); // A!B!|
	// testForm("AB|C&!"); // A!B!&C!|
	// testForm("AB|"); //AB|
	testForm("AB=C>"); // AB&A!B!&|C|
}
