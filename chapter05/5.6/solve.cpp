/*
 * TASK: Given a 32-bit integer, swap its even and odd bits, i.e., swap bits
 *       2*n and 2*n+1 for n = 0, 1, ..., 15, with n = 0 being the index of
 *       the LSB.
 */

#include <bitset>
#include <iostream>
#include <random>
#include <cassert>

/**
 * @brief given a 32-bit integer x, returns the integer resulting from swapping
 *        its even and odd bits using only bitwise operations
 * @note complexity: O(1) in both time and space
 */
uint32_t swap_bits(const uint32_t x)
{
	uint32_t even_mask = 0b01010101010101010101010101010101;
	uint32_t odd_mask  = 0b10101010101010101010101010101010;

	return ((x & even_mask) << 1U) | ((x & odd_mask) >> 1U);
}

int main()
{
	static std::random_device device;
	static std::mt19937 generator(device());

	std::uniform_int_distribution< uint32_t > distribution;

	for (int i = 0; i < 1000000; ++i)
	{
		uint32_t x = distribution(generator);
		uint32_t y = swap_bits(x);

		std::bitset< 32 > x_bits(x);
		std::bitset< 32 > y_bits(y);

		for (uint32_t i = 0; i < 32; i += 2)
		{
			assert(x_bits[i] == y_bits[i+1]);
			assert(y_bits[i] == x_bits[i+1]);
		}
	}

	std::cout << "passed random tests" << std::endl;

	return 0;
}

