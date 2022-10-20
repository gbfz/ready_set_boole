#pragma once
#include "ASTree.hpp"

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	AB&A!B!&|
 * Equivalence (2):		AB=		≡	A!B|AB!|&
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 * Distributivity I:	AB|C&	≡	CA&CB&|
 * Distributivity II:	AB&C|	≡	CA|CB|&
 */

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

/*
	const ast::tree distributivity1_in();
	ast::tree& rewriteDistr1_in(ast::tree& tree);

	const ast::tree distributivity1_out();
	ast::tree& rewriteDistr1_out(ast::tree& tree);

	const ast::tree distributivity2_in();
	ast::tree& rewriteDistr2_in(ast::tree& tree);

	const ast::tree distributivity2_out();
	ast::tree& rewriteDistr2_out(ast::tree& tree);
*/
}
