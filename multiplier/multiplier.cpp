#include "multiplier.hpp"
#include "adder.hpp"

namespace {

	auto multiplier_impl(uint32_t a, uint32_t b, uint32_t product) -> uint32_t {
		if (b == 0)
			return product;
		if (b & 1)
			product = adder(product, a);
		return multiplier_impl(a << 1, b >> 1, product);
	}

}

auto multiplier(uint32_t a, uint32_t b) -> uint32_t {
	return multiplier_impl(a, b, 0u);
}
