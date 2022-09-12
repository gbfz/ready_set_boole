#include <cstdint>

auto gray_code(uint32_t binary) -> uint32_t
{
	return binary ^ (binary >> 1);
}
