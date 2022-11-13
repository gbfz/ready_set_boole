#include "map.hpp"
#include "libmorton/include/libmorton/morton.h"
#include <iostream>
#include <cassert>

void test(uint16_t x, uint16_t y)
{
	double z = map(x, y);
	double libz = libmorton::morton2D_32_encode(x, y);

	libz /= std::numeric_limits<uint32_t>::max();
	std::cout << "Actual  : " << z << '\n';
	std::cout << "Expected: " << libz << '\n';
	assert(z == libz);
}

int main()
{
	test(0, 0);
	test(16, 42);
	test(100, 100);
	test(33451, 100);
	test(33451, 200);
	test(16000, 16000);
	test(42000, 42000);
	test(65535, 65535);
}
