#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <iostream>
#include "../negation_normal_form/NNForm.hpp"

namespace SE {

using set = std::set<int>;

std::vector<int> eval_set(
		std::string f, const std::vector<std::vector<int>>& sets);

}
