#include <bitset>
#include <iostream>

namespace {
	auto adder_impl(uint32_t sum, uint32_t carry) -> uint32_t
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
	auto multiplier_impl(int32_t prod, uint32_t orig, uint32_t i) -> uint32_t
	{
		if (i == 0)
			return prod;
		return multiplier_impl(adder(prod, orig), orig, i - 1);
	}
}

auto multiplier(uint32_t a, uint32_t b) -> uint32_t
{
	/*
	if (!a | !b)
		return 0u;
	return multiplier_impl(a, a, b - 1);
	*/
	// /*
	if (!a | !b)
		return 0;
	auto prod = a;
	while ((b += -1))
		prod = adder(prod, a);
	return prod;
	// */
}

template <typename T>
auto mul(T a, T b) -> T
{
}

auto test(uint32_t a, uint32_t b) -> void
{
	auto r = multiplier(a, b);
	if (r == a * b) {
		std::cout << "[" << a <<", " << b << "] :: good\n";
		return;
	}
	using bset = std::bitset<32>;
	std::cout << "a :=        " << bset(a) << '\n';
	std::cout << "b :=        " << bset(b) << '\n';
	std::cout << '\n';
	std::cout << "expected := " << bset(a * b) << '\n';
	std::cout << "actual   := " << bset(r) << '\n';
	std::cout << '\n';
	std::cout << "Error with a : " << a << " and b : " << b << '\n';
	std::exit(a * b);
}

auto main() -> int
{
	test(2, 2);
	test(0, 2);
	test(14, 5);
	test(420, 16);
	test(420, 16000);
	test(42000000, 16000);
}
