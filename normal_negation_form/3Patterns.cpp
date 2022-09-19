#include <iostream>
#include <unordered_map>
#include <map>
#include <optional>
#include <ranges>

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

/* AB|C&! -> DM2
 * AB|!C!| -> DM1
 * A!B!&C!|
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

static const std::unordered_map<Pattern, std::string> normal =
{
	{Pattern::DoubleNegation,	"a"},
	{Pattern::Implication,		"a!b|"},
	{Pattern::Equivalence,		"a1&a!b!&|"},
	{Pattern::DeMorgans1,		"a!b!&"},
	{Pattern::DeMorgans2,		"a!b!|"},
	{Pattern::Distr1,			"cb&ca&|"},
	{Pattern::Distr2,			"cb|ca|&"},
};

auto print_map(const auto& map) -> void
{
	std::cout << "Map:\n";
	for (const auto& [key, value] : map)
		std::cout << "Key: " << key << ", value: " << value << '\n';
}

auto match_pattern(std::string s) -> Pattern
{
	for (const auto& [key, value] : original)
		if (s.find(key) != std::string::npos)
			return value;
	throw std::runtime_error("Could not match pattern");
}

auto match_op(const std::string& s, char op) -> size_t
{
	auto i = s.find(op);
	if (i == std::string::npos)
		return std::string::npos;
	if (is_variable(s.at(i - 2)) && is_variable(s.at(i - 1)))
		return i - 2;
	return std::string::npos;
}

auto simplify(std::string& s,
			  std::map<char, std::string>& m,
			  char sub) -> void
{
	if (auto i = match_op(s, '|'); i != std::string::npos) {
		m.insert({sub, s.substr(i, 3)});
		s.replace(i, 3, {sub});
		return simplify(s, m, sub + 1);
	}
	if (auto i = match_op(s, '&'); i != std::string::npos) {
		m.insert({sub, s.substr(i, 3)});
		s.replace(i, 3, {sub});
		return simplify(s, m, sub + 1);
	}
}

auto reinstate(std::string& s,
			   std::map<char, std::string>& m,
			   size_t i) -> void
{
	if (i >= s.size())
		return;
	if (m.contains(s[i]))
		s.replace(i, 1, m[s[i]]);
	reinstate(s, m, i + 1);
}

auto testS(std::string s)
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
		std::cout << '\n';
	};
	std::map<char, std::string> m;
	char sub = 'a';
	simplify(s, m, sub);
	p(s);
	reinstate(s, m, 0);
	p(s);
	// p(negation_normal_form(s));
}

auto main() -> int
{
	auto p = [](auto&&... args) {
		((std::cout << args), ...);
		std::cout << '\n';
	};
	// testS("AB|DE&");
	testS("AB|C&!"); // aC&!
	// p(negation_normal_form("A|B!"));
}
