/*
 * TASK: For a given integer, determine the smallest larger and the largest
 *       smaller integer values which have the same number of bits set (i.e.,
 *       the same number of 1's) as the given integer in their binary
 *       representations. As an example, the smallest larger and largest
 *       smaller values for the binary number 1100 are 10001 and 1010
 *       respectively.
 *
 * NOTE: The solutions below assume that the input integer has 16 bits of
 *       length to make brute-force solving of the problem doable in a an
 *       acceptable amount of time, but the solutions can be directly extended
 *       to integers of arbitrary lengths (if we used 64-bit integers, however,
 *       brute-force testing as implemented here would take too long).
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief Returns the smallest integer which is larger than n but has the same
 *        number of bits set if such an integer exists, otherwise n itself is
 *        returned.
 * @note Complexity: O(1) in both time and space (technically O(num bits of n)
 *       if we did this for integers with arbitrary lengths).
 */
uint16_t smallest_larger_int_same_num_bits_1(uint16_t n)
{
    uint16_t m = n;
    uint16_t i = 0;

    /* move i to the left until it points to the first 1 of n */
    while (i < 16 && (m & 1) == 0)
    {
        ++i;
        m >>= 1;
    }

    /*
     * j is the position of the first 1 (starting from the right, i.e., from
     * the LSB of n towards its MSB) or 16 if n has no 1's (i.e., n == 0)
     */
    uint16_t j = i;

    /*
     * move i to the left until it points to the first 0 after the
     * rightmost sequence of 1's (i points initially to the rightmost
     * 1 of such a sequence)
     */
    while (i < 16 && (m & 1) == 1)
    {
        ++i;
        m >>= 1;
    }

    /*
     * if i reaches 16, n's binary representation is a (possibly empty)
     * sequence of 1's followed by a (possibly empty) sequence of 0's, in
     * which case there is no number which we can represent that is larger
     * than n and has the same number of 1's as n
     */
    if (i == 16)
    {
        return n;
    }

    /*
     * we must move the leftmost 1 on the rightmost sequence of 1's to the
     * left and all 1's that come before this 1 all the way to the right
     */
    m = n & ((1 << (i - 1)) - 1);
    n -= m;
    m >>= j;
    return n + (1 << i) - (1 << (i - 1)) + m;
}

/**
 * @brief Returns the largest integer which is smaller than n but has the same
 *        number of bits set if such an integer exists, otherwise n itself is
 *        returned.
 * @note Complexity: O(1) in both time and space (technically O(num bits of n)
 *       if we did this for integers with arbitrary lengths).
 */
uint16_t largest_smaller_int_same_num_bits_1(uint16_t n)
{
    uint16_t m = n;
    uint16_t i = 0;

    /* move i to the left until it points to the first 0 of n*/
    while (i < 16 && (m & 1) == 1)
    {
        ++i;
        m >>= 1;
    }

    /*
     * j is the position of the first 0 (starting from the right, i.e., from
     * the LSB of n towards its MSB) or 16 if n has no 1's (i.e., n == 0)
     */
    uint16_t j = i;

    /*
     * move i to the left until it points to the first 1 after the
     * rightmost sequence of 0's (i points initially to the rightmost
     * 0 of such a sequence)
     */
    while (i < 16 && (m & 1) == 0)
    {
        ++i;
        m >>= 1;
    }

    /*
     * if i reaches 16, n's binary representation is a (possibly empty)
     * sequence of 0's followed by a (possibly empty) sequence of 1's, in
     * which case there is no number which we can represent that is smaller
     * than n and has the same number of 1's as n
     */
    if (i == 16)
    {
        return n;
    }

    /*
     * we must move the leftmost 0 on the rightmost sequence of 0's to the
     * left and all 0's that come before this 0 all the way to the right
     */
    m = n & ((1 << (i - 1)) - 1);
    n -= m;
    m <<= i - 1 > j ? (i - j - 1) : 0;
    return n - (1 << i) + (1 << (i - 1)) + m;
}

/**
 * @brief Returns the number of bits set in n.
 * @note Complexity: O(1) in both time and space (technically O(num bits of n)
 *       if we did this for integers with arbitrary lengths).
 */
uint16_t get_num_bits_set(uint16_t n)
{
    uint16_t count = 0;

    while (n > 0)
    {
        count += n & 1;
        n >>= 1;
    }

    return count;
}

/**
 * @brief Returns the smallest integer which is larger than n but has the same
 *        number of bits set if such an integer exists, otherwise n itself is
 *        returned (brute force is used).
 * @note Complexity: O(1) in both time and space (technically O(2^(num bits of
 *       n)) if we did this for integers with arbitrary lengths).
 */
uint16_t smallest_larger_int_same_num_bits_2(const uint16_t n)
{
    uint64_t m = n;
    uint16_t bits_set = get_num_bits_set(n);

    while (m < std::numeric_limits<uint16_t>::max())
    {
        ++m;
        if (get_num_bits_set(m) == bits_set)
        {
            return m;
        }
    }

    return n;
}

/**
 * @brief Returns the largest integer which is smaller than n but has the same
 *        number of bits set if such an integer exists, otherwise n itself is
 *        returned (brute force is used).
 * @note Complexity: O(1) in both time and space (technically O(2^(num bits of
 *       n)) if we did this for integers with arbitrary lengths).
 */
uint16_t largest_smaller_int_same_num_bits_2(const uint16_t n)
{
    uint16_t m = n;
    uint16_t bits_set = get_num_bits_set(n);

    while (m > 0)
    {
        --m;
        if (get_num_bits_set(m) == bits_set)
        {
            return m;
        }
    }

    return n;
}

/**
 * @brief Generates a random unsigned 16-bit integer with n bits set.
 * @note Complexity: O(1) in both time and space.
 */
uint16_t random_number(uint16_t n)
{
    uint16_t number = 0;

    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<uint8_t> bit_chooser(0, 15);

    while (n > 0)
    {
        uint16_t index = bit_chooser(generator);

        if ((number & (1 << index)) == 0)
        {
            number |= 1 << index;
            --n;
        }
    }

    return number;
}

int main()
{
    for (uint16_t n = 0; n <= 16; ++n)
    {
        int num_tests = (n == 0 || n == 16) ? 1 : 1000;

        for (int i = 0; i < num_tests; ++i)
        {
            uint16_t number = random_number(n);

            assert(get_num_bits_set(number) == n);

            uint64_t larger_1 = largest_smaller_int_same_num_bits_1(number);
            uint64_t smaller_1 = smallest_larger_int_same_num_bits_1(number);

            uint64_t larger_2 = largest_smaller_int_same_num_bits_2(number);
            uint64_t smaller_2 = smallest_larger_int_same_num_bits_2(number);

            assert(get_num_bits_set(larger_1) == n);
            assert(get_num_bits_set(smaller_1) == n);

            assert(larger_1 == larger_2);
            assert(smaller_1 == smaller_2);
        }

        std::cout << "passed random tests for numbers with " << n << " bits set"
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
