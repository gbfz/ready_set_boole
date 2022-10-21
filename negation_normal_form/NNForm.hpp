#pragma once
#include "../ast/source/ASTree.hpp"
#include "Pattern.hpp"

namespace nnf {

	namespace detail {

		ast::tree& generateTree(ast::tree&);
		ast::tree& rewritePattern(ast::tree& tree);

		using funcT = decltype(&pattern::rewriteDoubleNegation);
		using PatternActionMap = std::vector<std::pair<ast::tree, funcT>>;

		const PatternActionMap& getPatternActionMap();
	}

	std::string negation_normal_form(std::string const& s);
}
