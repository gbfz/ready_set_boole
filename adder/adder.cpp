#include "adder.hpp"

namespace {

	auto adder_impl(uint32_t sum, uint32_t carry) -> uint32_t {
		if (carry == 0)
			return sum;
		return adder_impl(sum ^ (carry << 1), sum & (carry << 1));
	}

}

auto adder(uint32_t a, uint32_t b) -> uint32_t {
	return adder_impl(a ^ b, a & b);
}
