#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/container/deque.hpp>

#include <iostream>

namespace x3 = boost::spirit::x3;

namespace parser {

	using x3::_val;
	using x3::_attr;
	using x3::ascii::char_;

	const auto set_val = [](auto& ctx)
	{
		_val(ctx) = _attr(ctx) - '0';
	};

	const auto get_two_operands = [](auto& ctx) -> std::pair<int, int>
	{
		return { at_c<0>(_attr(ctx)), at_c<1>(_attr(ctx)) };
	};

	const auto and_op = [](auto& ctx)
	{
		auto [fst, snd] = get_two_operands(ctx);
		_val(ctx) = fst & snd;
	};

	const auto or_op = [](auto& ctx)
	{
		auto [fst, snd] = get_two_operands(ctx);
		_val(ctx) = fst | snd;
	};

	x3::rule<class Expr, int> expr_ = "expr";
	x3::rule<class And,  int> and_	= "and";
	x3::rule<class Or,   int> or_	= "or";
	x3::rule<class Val,  int> val	= "val";

	/* There should be some basic "node"
	 * which is to be a variant of either a primitive or and operation
	 */

	const auto expr__def = and_ | or_;
	// const auto and__def = ((val >> val) >> char_('&')) [and_op];
	// const auto or__def  = ((val >> val) >> char_('|')) [or_op];
	const auto and__def = ((val >> val) >> char_('&')) [and_op]
						| (expr_ >> char_('&'));

	const auto or__def  = ((val >> val) >> char_('|')) [or_op]
						| (expr_ >> char_('|'));

	const auto val_def = char_('1') [set_val]
					   | char_('0') [set_val];

	BOOST_SPIRIT_DEFINE(expr_, and_, or_, val);
}

int main()
{
	std::string s = "10|1&";
	int yeah;
	auto iter = s.begin();
	bool r = boost::spirit::x3::parse(iter, s.end(), parser::expr_, yeah);
	if (r && iter == s.end())
	{
		std::cout << "-------------------------\n";
		std::cout << "Parsing succeeded\n";
		std::cout << "Result = " << yeah << std::endl;
		std::cout << "-------------------------\n";
	}
	else
	{
		std::string rest(iter, s.end());
		std::cout << "-------------------------\n";
		std::cout << "Parsing failed\n";
		std::cout << "stopped at: \": " << rest << "\"\n";
		std::cout << "-------------------------\n";
	}
}
