#include <list>
#include <iterator>	/* std::next, std::begin, std::end */
#include <iostream>
#include <random>	/* std::uniform_int_distribution */
#include <cassert>

/* a decimal digit (value on range [0,9]) */
typedef uint8_t digit;

/* a number represented as a list of decimal digits (in reverse order) */
typedef std::list< digit > number;

/**
 * @brief returns the sum of two numbers stored as linked lists
 * @param a a number stored as a linked list
 * @param b a number stored as a linked list
 * @return a + b stored as a linked list
 * @note complexity: O(m+n) in time, O(max(m,n)) in space, where m and n are
 *       the number of digits in a and b respectively
 */
number add_numbers(const number& a, const number& b)
{
	number sum;

	auto a_it = std::begin(a);
	auto b_it = std::begin(b);

	digit carry = 0;

	while (a_it != std::end(a) && b_it != std::end(b))
	{
		sum.push_back(((*a_it + *b_it) % 10) + carry);
		carry = (*a_it + *b_it) / 10;

		a_it = std::next(a_it);
		b_it = std::next(b_it);
	}

	/* if a and b have the same number of digits but we have a carry */
	if (a_it == std::end(a) && b_it == std::end(b) && carry > 0)
	{
		sum.push_back(carry);
	}

	/* this loop runs if b has less digits than a */
	while (a_it != std::end(a))
	{
		sum.push_back(*a_it + carry);
		a_it = std::next(a_it);
		carry = 0;
	}

	/* this loop runs if a has less digits than b */
	while (b_it != std::end(b))
	{
		sum.push_back(*b_it + carry);
		b_it = std::next(b_it);
		carry = 0;
	}

	return sum;
}

/**
 * @brief converts a number stored as a list to a uint64_t
 * @note complexity: O(n) in time, O(1) in space, where n is the number of
 *       digits in a (a must fit on a uint64_t, otherwise this will fail)
 */
uint64_t to_integer(const number& a)
{
	uint64_t number = 0;
	uint64_t factor = 1;

	for (const digit& d : a)
	{
		number += factor * d;
		factor *= 10;
	}
	return number;
}

/**
 * @brief converts a number stored as a uint64_t to a list
 */
number to_list(uint64_t n)
{
	number a;

	while (n > 0)
	{
		a.push_back(n % 10);
		n /= 10;
	}

	return a;
}

int main()
{
	std::random_device device;
	std::mt19937 generator(device());

	for (size_t n = 1; n <= 1000000000000; n *= 10)
	{
		for (size_t i = 0; i < 1000; ++i)
		{
			std::uniform_int_distribution< uint64_t > distribution(0,n);

			uint64_t na = distribution(generator);
			uint64_t nb = distribution(generator);

			number a = to_list(na);
			number b = to_list(nb);

			assert(to_integer(a) == na);
			assert(to_integer(b) == nb);

			number sum = add_numbers(a,b);

			assert(to_integer(a) + to_integer(b) == to_integer(sum));
		}

		std::cout << "passed tests for numbers up to " << n << std::endl;
	}

	return 0;
}
