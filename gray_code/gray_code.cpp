#include "gray_code.hpp"

auto gray_code(uint32_t n) -> uint32_t {
	return n ^ (n >> 1);
}
