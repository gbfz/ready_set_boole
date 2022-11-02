#include "powerset.hpp"
#include <iostream>

int main()
{
	// auto w = powerset({'a','b','c'});
	// auto w = powerset({1, 2, 3});
	// auto w = powerset({1});
	// auto w = powerset({});
	auto w = powerset({3, 14, 15, 92, 6});
	std::cout << "size = " << w.size() << '\n';
	for (auto&& v : w)
	{
		if (v.empty())
		{
			std::cout << "Ø\n";
			continue;
		}
		for (int i : v)
			std::cout << i << ' ';
		std::cout << '\n';
	}
}
