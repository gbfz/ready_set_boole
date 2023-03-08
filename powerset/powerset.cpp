#include "powerset.hpp"

std::vector<std::vector<int>> powerset(std::vector<int> const& v)
{
	std::vector<std::vector<int>> out;

	for (int elem : v)
	{
		for (int i = 0, size = out.size(); i < size; ++i)
		{
			auto new_set { out[i] };
			new_set.push_back(elem);
			out.emplace_back(std::move(new_set));
		}
		out.emplace_back(std::vector<int> { elem } );
	}
	out.emplace_back(std::vector<int> {});
	return out;
}
