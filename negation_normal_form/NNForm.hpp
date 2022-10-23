#pragma once
#include "Pattern.hpp"

namespace nnf {

	namespace detail {

		ast::tree& generateTree(ast::tree&);
		ast::tree& rewritePattern(ast::tree& tree);

		using funcT = decltype(&pattern::rewriteDoubleNegation);
		using PatternRewriteMap = std::vector<std::pair<ast::tree, funcT>>;

		const PatternRewriteMap& getPatternRewriteMap();
	}

	std::string negation_normal_form(std::string const& s);
}
