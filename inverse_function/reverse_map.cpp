#include "reverse_map.hpp"

#include <limits>

namespace {

	uint32_t deinterleave(uint32_t x)
	{
		x =  x             & 0b1010101010101010101010101010101;
		x = (x | (x >> 1)) & 0b0110011001100110011001100110011;
		x = (x | (x >> 2)) & 0b0001111000011110000111100001111;
		x = (x | (x >> 4)) & 0b0000000111111110000000011111111;
		x = (x | (x >> 8)) & 0b0000000000000001111111111111111;
		return x;
	}

}

std::pair<uint16_t, uint16_t> reverse_map(double n)
{
	uint32_t z = n * std::numeric_limits<uint32_t>::max();
	return { deinterleave(z), deinterleave(z >> 1) };
}
