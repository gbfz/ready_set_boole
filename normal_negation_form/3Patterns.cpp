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

/* AB=C>
 * AB&A!B!&|C>
 * aC>
 */

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

enum class Pattern
{
	DoubleNegation,
	Implication,
	Equivalence,
	DeMorgans1,
	DeMorgans2,
	Distr1,
	Distr2,
	And,
	Or,
};

static const std::unordered_map<std::string, Pattern> original =
{
	{"!!",	Pattern::DoubleNegation},
	{">",	Pattern::Implication},
	{"=",	Pattern::Equivalence},
	{"|!",	Pattern::DeMorgans1},
	{"&!",	Pattern::DeMorgans2},
	{"|&",	Pattern::Distr1},
	{"&|",	Pattern::Distr2},
};

auto is_normal_form(const std::string& s) -> bool
{
	static const std::regex exp("!!|\\|!|&!|>|=");
	return !std::regex_search(s, exp);
}

auto rewrite_double_negation(std::string& s)
{
	// s.erase(s.find("!!"), 2);
	auto pos = s.find("!!");
	auto replacement = {s.at(pos - 1)};
	s.replace(pos - 1, 2, replacement);
}

auto rewrite_implication(std::string& s)
{
	auto pos = s.find(">");
	auto replacement = {s.at(pos - 2), '!', s.at(pos - 1), '|'};
	s.replace(pos - 2, 3, replacement);
}

auto rewrite_equivalence(std::string& s)
{
	auto pos = s.find("=");
	auto a = s.at(pos - 2);
	auto b = s.at(pos - 1);
	auto replacement = {a, b, '&', a, '!', b, '!', '&', '|'};
	s.replace(pos - 2, 3, replacement);
}

auto rewrite_deMorgans1(std::string& s)
{
	auto pos = s.find("|!");
	auto replacement = {s.at(pos - 2), '!', s.at(pos - 1), '!', '|'};
	s.replace(pos - 2, 4, replacement);
}

auto rewrite_deMorgans2(std::string& s)
{
	auto pos = s.find("&!");
	auto replacement = {s.at(pos - 2), '!', s.at(pos - 1), '!', '&'};
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

auto match_op(const std::string& s, char op) -> size_t
{
	auto i = s.find(op);
	if (i == std::string::npos)
		return std::string::npos;
	if (is_single_binary_operation(s, i))
		return i - 2;
	return std::string::npos;
}

auto simplify(std::string& s,
			  std::map<char, std::string>& m,
			  char sub) -> void;

auto simplify_and_save(std::string& s,
					   std::map<char, std::string>& m,
					   char sub,
					   size_t pos) -> void
{
	m.insert({sub, s.substr(pos, 3)});
	s.replace(pos, 3, {sub});
	return simplify(s, m, sub + 1);
}

auto simplify(std::string& s,
			  std::map<char, std::string>& m,
			  char sub) -> void
{
	if (auto i = match_op(s, '|'); i != std::string::npos)
		return simplify_and_save(s, m, sub, i);
	if (auto i = match_op(s, '&'); i != std::string::npos)
		return simplify_and_save(s, m, sub, i);
}

auto reinstate(std::string& s,
			   std::map<char, std::string>& m,
			   size_t i) -> void
{
	if (i >= s.size())
		return;
	if (m.contains(s[i])) {
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
	std::cerr << matched_str.str(0) << '\n';
	std::cerr << matched_str.str() << '\n';
	throw std::runtime_error("Fuck");
}

auto negation_normal_form(std::string s) -> std::string
{
	std::map<char, std::string> simp_map;
	while (!is_normal_form(s))
	{
		simplify(s, simp_map, 'a');
		std::cout << "s1: " << s << '\n';
		rewrite(s, match_pattern(s));
		std::cout << "s2: " << s << '\n';
		reinstate(s, simp_map, 0);
		std::cout << "s3: " << s << '\n';
	}
	return s;
}

auto testSimRei(std::string s)
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
		std::cout << '\n';
	};
	std::map<char, std::string> m;
	simplify(s, m, 'a');
	p(s);
	reinstate(s, m, 0);
	p(s);
}

auto testForm(const std::string& s)
{
	auto p = [](auto&&... args) {
		((std::cout << std::boolalpha << args), ...);
		std::cout << '\n';
	};
	p(negation_normal_form(s));
}

auto main() -> int
{
	// testForm("AB|C&!");
	// testForm("AB|");
	// testForm("AB=C>");
	testSimRei("AB=C>");
}
