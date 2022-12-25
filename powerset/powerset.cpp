#include "powerset.hpp"

std::vector<std::vector<int>> powerset(const std::vector<int>& v)
{
	std::vector<std::vector<int>> pset;
	std::vector<int> branch;

	auto accumulateSubsets = [&](size_t start, auto&& acc) -> decltype(pset)
	{
		pset.emplace_back(branch);
		for (size_t i = start; i < v.size(); ++i)
		{
			branch.emplace_back(v[i]);
			acc(i + 1, acc);
			branch.pop_back();
		}
		return pset;
	};
	return accumulateSubsets(0, accumulateSubsets);
}
