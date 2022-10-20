#pragma once
#include "ASTree.hpp"
#include "Pattern.hpp"

namespace nnf {

	namespace detail {

		ast::tree& negation_normal_form(ast::tree&);
		ast::tree& rewrite(ast::tree& tree);

	} // detail

	std::string negation_normal_form(const std::string& s);

}
