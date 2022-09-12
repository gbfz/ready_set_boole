#include <iostream>
#include <bitset>

auto multiplier(uint32_t a, uint32_t b) -> uint32_t;

auto test(uint32_t a, uint32_t b) -> void
{
	auto r = multiplier(a, b);
	if (r == a * b) {
		std::cout << "[" << a << ", " << b << "] :: good\n";
		return;
	}
	using bin = std::bitset<32>;
	std::cout << "a :=        " << bin(a) << '\n';
	std::cout << "b :=        " << bin(b) << "\n\n";
	std::cout << "expected := " << bin(a * b) << '\n';
	std::cout << "actual   := " << bin(r) << "\n\n";
	std::cout << "Error with a : " << a << ", b : " << b << '\n';
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

