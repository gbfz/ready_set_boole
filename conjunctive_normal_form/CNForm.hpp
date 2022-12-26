#pragma once
#include "../negation_normal_form/NNForm.hpp"
#include "CNFPattern.hpp"

namespace cnf {

	namespace detail {

		ast::tree& generateTree(ast::tree& tree);
		ast::tree& rewritePattern(ast::tree& tree);

		using funcT = decltype(&pattern::rewriteDocL);
		using PatternRewriteMap = std::vector<std::pair<ast::tree, funcT>>;

		const PatternRewriteMap& getPatternRewriteMap();
	}

	std::string conjunctive_normal_form(const std::string& s);

}
