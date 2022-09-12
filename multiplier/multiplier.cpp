#include <concepts>
#include <cstdint>

namespace {
	template <class T> requires std::unsigned_integral<T>
	auto adder_impl(T sum, T carry)
	{
		if (!carry)
			return sum;
		return adder_impl(sum ^ (carry << 1), sum & (carry << 1));
	}
}

auto adder(uint32_t a, uint32_t b) -> uint32_t
{
	return adder_impl(a ^ b, a & b);
}

namespace {
	template <class T> requires std::unsigned_integral<T>
	auto multiplier_impl(T a, T b, T product)
	{
		if (b == 0)
			return product;
		if (b & 1)
			product = adder(product, a);
		return multiplier_impl(a << 1, b >> 1, product);
	}
}

auto multiplier(uint32_t a, uint32_t b) -> uint32_t
{
	return multiplier_impl(a, b, 0u);
}
