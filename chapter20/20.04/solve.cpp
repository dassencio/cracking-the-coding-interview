/*
 * TASK: Given a nonnegative integer n, determine how many times the digit '2'
 *       appears in total on the decimal representations of all numbers in
 *       [0,n].
 */

#include <iostream>
#include <cassert>

/**
 * @brief returns the number of '2's in a nonnegative integer n
 * @note complexity: O(log10(n)) in time, O(1) in space, since the number of
 *       digits in n is log10(n) + 1
 */
int count_twos_in_number(int n)
{
	int count = 0;

	while (n > 0)
	{
		count += (n % 10 == 2);
		n /= 10;
	}

	return count;
}

/**
 * @brief determines the number of '2's in the range [0,n] using brute force
 * @note complexity: O(n*log10(n)) in in time, O(1) in space, since the number
 *       of digits in n is log10(n) + 1
 */
int count_twos_in_range_1(const int n)
{
	int count = 0;

	for (int i = 0; i <= n; ++i)
	{
		count += count_twos_in_number(i);
	}

	return count;
}

/**
 * @brief determines the number of '2's in the range [0,n] recursively
 * @note complexity: O(2^log10(n)) in time, O(log10(n)) in space, since the
 *       number of digits in n is log10(n) + 1
 */
int count_twos_in_range_2(const int n)
{
	/* base case: n is a one-digit integer */
	if (n < 10)
	{
		return n >= 2;
	}

	int factor = 1;

	/* factor is the largest power of 10 such that n/factor > 0 */
	while (n / factor >= 10)
	{
		factor *= 10;
	}

	int highest_digit = n / factor;
	int remainder = n % factor;

	/*
	 * each call to count_twos_in_range_2 sends a number with one digit
	 * less than n as parameter, so the recursion does not go deeper than
	 * O(log10(n)) levels
	 */
	return highest_digit * count_twos_in_range_2(factor - 1)
	     + count_twos_in_range_2(remainder)
	     + (highest_digit > 2) * factor
	     + (highest_digit == 2) * (remainder + 1);
}

int main()
{
	for (int n = 0; n < 10000; ++n)
	{
		assert(count_twos_in_range_1(n) == count_twos_in_range_2(n));
	}

	std::cout << "passed all tests" << std::endl;

	return 0;
}
