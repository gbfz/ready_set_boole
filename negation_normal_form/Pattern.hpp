#pragma once
#include "../ast/source/ASTree.hpp"

namespace nnf::pattern {

	const ast::tree doubleNegationPattern();
	ast::tree& rewriteDoubleNegation(ast::tree& tree);

	const ast::tree implicationPattern();
	ast::tree& rewriteImplication(ast::tree& tree);

	const ast::tree equivalencePattern();
	ast::tree& rewriteEquivalence(ast::tree& tree);

	const ast::tree deMorgans1Pattern();
	ast::tree& rewriteDeMorgans1(ast::tree& tree);

	const ast::tree deMorgans2Pattern();
	ast::tree& rewriteDeMorgans2(ast::tree& tree);

}
