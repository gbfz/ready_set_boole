#pragma once
#include "ASTree.hpp"

namespace cnf::pattern {

	// doc  ⇔  disjunction over conjunction
	const ast::tree docPatternL();
	ast::tree& rewriteDocL(ast::tree& tree);

	const ast::tree docPatternR();
	ast::tree& rewriteDocR(ast::tree& tree);

	const ast::tree doubleDisjunctionPattern();
	ast::tree& rewriteDoubleDisjunction(ast::tree& tree);

	const ast::tree doubleConjunctionPattern();
	ast::tree& rewriteDoubleConjunction(ast::tree& tree);
}
