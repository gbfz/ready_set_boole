#include "adder.hpp"
#include <concepts>

namespace {

	template <std::unsigned_integral T>
	auto adder_impl(T sum, T carry) -> T {
		if (carry == 0)
			return sum;
		return adder_impl(sum ^ (carry << 1), sum & (carry << 1));
	}

}

auto adder(uint32_t a, uint32_t b) -> uint32_t {
	return adder_impl(a ^ b, a & b);
}
