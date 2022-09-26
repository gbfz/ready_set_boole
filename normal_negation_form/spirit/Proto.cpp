#include <boost/spirit/home/x3.hpp>

#include <iostream>

namespace x3 = boost::spirit::x3;

namespace parser {

	using x3::_val;
	using x3::_attr;
	using x3::ascii::char_;

	const auto set_primitive = [](auto& ctx)
	{
		_val(ctx) = get<char>(_attr(ctx)) - '0';
	};

	const auto single_binary_operation = [](int fst, int snd, char op) -> int
	{
		switch (op)
		{
			case '&': return fst & snd;
			case '|': return fst | snd;
			case '^': return fst ^ snd;
			case '>': return fst ? snd : 1;
			case '=': return fst == snd;
		}
		throw std::runtime_error("How tf did u get here");
	};

	const auto basic_binary_operation = [](auto& ctx)
	{
		int fst = at_c<0>(_attr(ctx));
		int snd = at_c<1>(_attr(ctx));
		char op = at_c<2>(_attr(ctx));
		_val(ctx) = single_binary_operation(fst, snd, op);
	};

	const auto compound_binary_operation = [](auto& ctx)
	{
		_val(ctx) = at_c<0>(_attr(ctx));
		for (const auto& p : at_c<1>(_attr(ctx)))
		{
			int snd = at_c<0>(p);
			char op = at_c<1>(p);
			_val(ctx) = single_binary_operation(_val(ctx), snd, op);
		}
	};

	x3::rule<class Start, int> start = "expr";
	x3::rule<class Operation, char> operation = "operation";
	x3::rule<class Token, int> token = "single token";
	x3::rule<class Primitive, int> primitive = "primitive";

	const auto start_def	 = (token >> *(primitive >> operation))		[compound_binary_operation];

	const auto token_def	 = (primitive >> primitive >> operation)	[basic_binary_operation];

	const auto primitive_def = (char_('1') | char_('0'))				[set_primitive];

	const auto operation_def = char_('&') | char_('|') | char_('^') | char_('>') | char_('=');

	BOOST_SPIRIT_DEFINE(start, operation, token, primitive);
}

int main()
{
	std::string s = "11&0^0=";
	int yeah;
	auto iter = s.begin();
	bool r = boost::spirit::x3::parse(iter, s.end(), parser::start, yeah);
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
		std::cout << "Stopped at: \": " << rest << "\"\n";
		std::cout << "-------------------------\n";
	}
}
