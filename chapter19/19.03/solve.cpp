/*
 * TASK: Given a nonnegative integer n, determine the number of trailing zeros
 *       in n!. As an example, for n = 9, the answer should be 1 since
 *       9! = 362880 and for n = 10, the answer should be 2 since n! = 3628800.
 */

#include <cmath>
#include <iostream>
#include <cassert>

/**
 * @brief Computes n!.
 * @note Complexity: O(n) in time, O(1) in space.
 */
uint64_t factorial(uint64_t n)
{
	uint64_t result = 1;

	while (n > 0)
	{
		result *= n;
		--n;
	}

	return result;
}

/**
 * @brief Returns the number of trailing zeros in n!.
 * @note Complexity: for an arbitrary-precision integer type, O(n*log(n)) in
 *       time, O(1) in space since n! has O(log(n!)) decimal digits (this is
 *       easy to see for log10)  and log(n!) ~ n*log(n) for very large n (from
 *       Stirling's approximation).
 */
uint64_t trailing_zeros_1(uint64_t n)
{
	uint64_t nfac = factorial(n);
	uint64_t count = 0;

	while (nfac > 0 && (nfac % 10) == 0)
	{
		++count;
		nfac /= 10;
	}

	return count;
}

/**
 * @brief Returns the number of trailing zeros in n!.
 * @note Complexity: for an arbitrary-precision integer type, O(n*log(n)) in
 *       time, O(1) in space since we divide O(n) integer values O(log(n)) times
 *       by 5 (but this method is still considerably faster than the other one
 *       since it does not involve multiplying very large numbers; also, since
 *       we do not compute n! here, we can actually use it for any 64-bit
 *       unsigned integer n).
 */
uint64_t trailing_zeros_2(uint64_t n)
{
	/*
	 * n! has as many zeros as the number of times it can be divided
	 * by 10. Since being divisible by 10 means being divisible by both
	 * 2 and 5, and since n! can always be divided by 2 more often than by
	 * 5, we just need to count the number of times n! can be divided by 5,
	 * and we do that by counting the number of times we can divide the
	 * following numbers by 5: n, n-1, ..., 5
	 */
	uint64_t count = 0;

	while (n >= 5)
	{
		uint64_t m = n;

		while (m >= 5)
		{
			if (m % 5 == 0)
			{
				++count;
				m /= 5;
			}
			else
			{
				break;
			}
		}

		--n;
	}

	return count;
}

int main()
{
	for (uint64_t n = 0; n <= 20; ++n)
	{
		assert(trailing_zeros_1(n) == trailing_zeros_2(n));

		std::cout << "passed test for n = " << n << std::endl;
	}
}
