#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <iostream>

namespace x3 = boost::spirit::x3;

namespace ast {

	struct node;

	struct node_value : x3::variant<int, x3::forward_ast<node>>
	{
		using base_type::base_type;
		using base_type::operator=;
	};

	using node_map = std::map<int, node_value>;
	using node_key_value = std::pair<int, node_value>;

	struct node
	{
		node_map entries;
	};

} // namespace ast

namespace parser::utils {

	using x3::_val;
	using x3::_attr;

} // namespace parser::utils

namespace parser {

	using x3::ascii::char_;

	x3::rule<class Primitive>			primitive			= "primitive";
	x3::rule<class UnaryOperator>		unary_operator		= "unary operator";
	x3::rule<class BinaryOperator>		binary_operator		= "binary operator";
	x3::rule<class CompoundOperation>	compound_operation	= "compound operation";

	const auto primitive_def			= char_('1') | char_('0');
	const auto unary_operator_def		= char_('!');
	const auto binary_operator_def		= char_('&') | char_('|') | char_('^') | char_('>') | char_('=');

	const auto compound_operation_def	= (primitive >> primitive >> binary_operator)
									 >> *((primitive >> binary_operator) | unary_operator);

	x3::rule<class Node, ast::node>		operation			= "operation";
	x3::rule<class NodeValue>			operation_value		= "operation value";
	x3::rule<class NodeKeyValue>		operation_key_value	= "operation key value";
	x3::rule<class Start, ast::node>	start				= "start";

	const auto operation_value_def		= compound_operation | operation;
	const auto operation_key_value_def	= compound_operation >> *operation_value;
	const auto operation_def			= +operation_key_value;
	const auto start_def				= (primitive >> unary_operator) | operation;

	BOOST_SPIRIT_DEFINE(start,
						binary_operator, unary_operator,
						primitive, compound_operation,
						operation_value, operation_key_value, operation);

} // namespace parser

int main()
{
	std::string s = "1!";
	// std::string s = "11!";
	// std::string s = "11|!!!1&1|1=";
	// std::string s = "11|1!";
	// int yeah;
	ast::node yeah;
	auto iter = s.begin();
	bool r = boost::spirit::x3::parse(iter, s.end(), parser::start, yeah);
	if (r && iter == s.end())
	{
		std::cout << "-------------------------\n";
		std::cout << "Parsing succeeded\n";
		// std::cout << "Result = " << yeah << std::endl;
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
