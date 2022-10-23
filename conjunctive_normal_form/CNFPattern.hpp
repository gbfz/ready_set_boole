#pragma once
#include "ASTree.hpp"

namespace cnf::pattern {
	const ast::tree disOverConPattern();
	ast::tree& rewriteDisOverCon(ast::tree& tree);
}
