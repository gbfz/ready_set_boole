#pragma once
#include "../ast/source/ASTree.hpp"

namespace cnf::pattern {
	const ast::tree disOverCon(); // p | (q & r) -> (p | q) & (p | r)
	ast::tree& rewriteDisOverCon(ast::tree& tree);
}
