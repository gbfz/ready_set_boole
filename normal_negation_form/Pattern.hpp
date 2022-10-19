#pragma once
#include "ASTree.hpp"

/* Patterns:
 *
 * Double negation:		A!!		≡	A
 * Implication:			AB>		≡	A!B|
 * Equivalence:			AB=		≡	AB&A!B!&|
 * De Morgan's I:		AB|!	≡	A!B!&
 * De Morgan's II:		AB&! 	≡	A!B!|
 * Distributivity I:	AB|C&	≡	CA&CB&|
 * Distributivity II:	AB&C|	≡	CA|CB|&
 */

namespace pattern {

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

	const ast::tree distributivity1_in();
	ast::tree& rewriteDistributivity1_in(ast::tree& tree);

	const ast::tree distributivity1_out();
	ast::tree& rewriteDistributivity1_out(ast::tree& tree);

	const ast::tree distributivity2_in();
	ast::tree& rewriteDistributivity2_in(ast::tree& tree);

	const ast::tree distributivity2_out();
	ast::tree& rewriteDistributivity2_out(ast::tree& tree);
}
