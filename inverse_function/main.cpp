#include "reverse_map.hpp"
#include <iostream>
#include <cassert>
#include "libmorton/include/libmorton/morton.h"

void test(double n)
{
	auto [x, y] = reverse_map(n);
	uint_fast16_t i, j;
	libmorton::morton2D_32_decode(n * std::numeric_limits<uint32_t>::max(), i, j);
	assert(x == i && y == j);
}

int main()
{
	test(0);
	test(0.0000022);
	test(0.345);
}
