#pragma once

#include <string>
#include <vector>

auto eval_set(std::string formula,
              std::vector<std::vector<int>> const& sets)
	-> std::vector<int>;
