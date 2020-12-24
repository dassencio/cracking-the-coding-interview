/*
 * TASK: You are given two numbers stored as linked lists. Each node of these
 *       lists stores a single digit of its associated number, and the digits
 *       are stored in reverse order, i.e., the least significant digit is the
 *       first element in the list and the most significant digit is the last
 *       element in the list. Compute the sum of the two given numbers and
 *       return the sum using the same (list) representation. As an example,
 *       215 + 58 = 273 is represented as {5,1,2} + {8,5} = {3,7,2}.
 */

#include <cassert>
#include <iostream>
#include <list>
#include <random>

/* a decimal digit (value on range [0,9]) */
using digit = uint8_t;

/* a number represented as a list of decimal digits (in reverse order) */
using number = std::list<digit>;

/**
 * @brief Returns the sum of two numbers stored as linked lists.
 * @param a A number stored as a linked list.
 * @param b B number stored as a linked list.
 * @return a + b stored as a linked list.
 * @note Complexity: O(m+n) in time, O(max(m,n)) in space, where m and n are
 *       the number of digits in a and b respectively.
 */
number add_numbers(const number& a, const number& b)
{
    number sum;

    auto a_it = a.begin();
    auto b_it = b.begin();

    digit carry = 0;

    while (a_it != a.end() && b_it != b.end())
    {
        sum.push_back(((*a_it + *b_it) % 10) + carry);
        carry = (*a_it + *b_it) / 10;

        ++a_it;
        ++b_it;
    }

    /* if a and b have the same number of digits but we have a carry */
    if (a_it == a.end() && b_it == b.end() && carry > 0)
    {
        sum.push_back(carry);
    }

    /* this loop runs if b has less digits than a */
    while (a_it != a.end())
    {
        sum.push_back(*a_it + carry);
        ++a_it;
        carry = 0;
    }

    /* this loop runs if a has less digits than b */
    while (b_it != b.end())
    {
        sum.push_back(*b_it + carry);
        ++b_it;
        carry = 0;
    }

    return sum;
}

/**
 * @brief Converts a number stored as a list to a uint64_t.
 * @note Complexity: O(n) in time, O(1) in space, where n is the number of
 *       digits in a (a must fit on a uint64_t, otherwise this will fail).
 */
uint64_t to_integer(const number& a)
{
    uint64_t na = 0;
    uint64_t factor = 1;

    for (const digit& d : a)
    {
        na += factor * d;
        factor *= 10;
    }

    return na;
}

/**
 * @brief Converts a number stored as a uint64_t to a list.
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

    for (uint64_t n = 1; n <= 1000000000000; n *= 10)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::uniform_int_distribution<uint64_t> distribution(0, n);

            uint64_t na = distribution(generator);
            uint64_t nb = distribution(generator);

            number a = to_list(na);
            number b = to_list(nb);

            assert(to_integer(a) == na);
            assert(to_integer(b) == nb);

            number sum = add_numbers(a, b);

            assert(to_integer(a) + to_integer(b) == to_integer(sum));
        }

        std::cout << "passed random tests for numbers up to " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
