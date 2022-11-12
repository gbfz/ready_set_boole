#include "map.hpp"
#include <iostream>

int main()
{
	auto test = [](auto x, auto y)
	{
		std::cout << "x: " << x << "\ny: " << y << '\n';
		std::cout << "z: " << map(x, y) << "\n\n";
	};
	test(0, 0);
	test(16, 42);
	test(100, 100);
	test(33451, 100);
	test(33451, 200);
	test(16000, 16000);
	test(42000, 42000);
	test(65535, 65535);
}
