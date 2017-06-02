/*
 * TASK: Given two nonnegative integers, add them without using any arithmetic
 *       operators, i.e., without using + - * /.
 */

#include <iostream>
#include <random>
#include <cassert>

/**
 * @brief Adds two integers a and b without arithmetic operations.
 * @note Complexity: O(n) in both time and space, where n is the number of
 *       bits in the input numbers (here fixed, but could be arbitrary).
 */
uint32_t add_1(uint32_t a, uint32_t b)
{
	uint32_t sum = 0;
	uint32_t carry = 0;

	/* do the sum bit-by-bit */
	for (uint32_t i = 0; i < 32; ++i)
	{
		uint32_t mask = 1U << i;

		/*
		 * ai and bi are the i-th bits of a and b respectively if the
		 * rightmost bit is the 0-th one
		 */
		uint32_t ai = (a & mask) >> i;
		uint32_t bi = (b & mask) >> i;

		if (ai == 0 || bi == 0)
		{
			sum |= ((ai | bi) ^ carry) << i;
			carry &= (ai | bi);
		}
		else /* ai == 1U && bi == 1U */
		{
			sum |= carry << i;
			carry = 1U;
		}
	}

	return sum;
}

/**
 * @brief Adds two integers a and b without arithmetic operations.
 * @note Complexity: O(n) in time, O(n²) in space, where n is the number of
 *       bits in the input numbers (here fixed, but could be arbitrary).
 * @note The recursion is guaranteed to converge because carry_values always
 *       have an added zero bit at each recursion step.
 */
uint32_t add_2(const uint32_t a, const uint32_t b)
{
	if (b == 0)
	{
		return a;
	}

	/* compute the sum of a and b without carry values */
	uint32_t sum_no_carry = a ^ b;

	/* compute all carry values */
	uint32_t carry_values = (a & b) << 1;

	return add_2(sum_no_carry, carry_values);
}

int main()
{
	std::random_device device;
	std::mt19937 generator(device());

	std::uniform_int_distribution< uint32_t > distribution;

	for (int i = 0; i < 1000000; ++i)
	{
		uint32_t a = distribution(generator);
		uint32_t b = distribution(generator);

		assert(add_1(a,b) == (a+b));
		assert(add_2(a,b) == (a+b));
	}

	std::cout << "passed all random tests" << std::endl;

	return EXIT_SUCCESS;
}
