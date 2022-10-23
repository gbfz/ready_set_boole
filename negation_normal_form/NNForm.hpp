#pragma once
<<<<<<< HEAD
#include "Pattern.hpp"
=======
#include "../ast/source/ASTree.hpp"
#include "NNFPattern.hpp"
>>>>>>> 85122e0119580b11d3c2fa634dce7344f40c5e85

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
