#include "powerset.hpp"
#include <cstddef>

std::vector<std::vector<int>> powerset(const std::vector<int>& v)
{
	std::vector<std::vector<int>> pset;
	std::vector<int> branch;

	auto accumulateSubsets = [&](size_t start, auto&& this_fun) -> decltype(pset)
	{
		pset.emplace_back(branch);
		for (auto i = start; i < v.size(); ++i)
		{
			branch.emplace_back(v[i]);
			this_fun(i + 1, this_fun);
			branch.pop_back();
		}
		return pset;
	};
	return accumulateSubsets(0, accumulateSubsets);
}
