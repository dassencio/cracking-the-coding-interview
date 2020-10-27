/*
 * TASK: You are given two integer values x and y. Determine the number of
 *       bits which differ on the binary representations of x and y. As an
 *       example, if the binary representations of x and y are 10001 and
 *       10010 respectively, the number of different bits is 2.
 */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief Returns the number of bits in x which differ from y.
 * @note Complexity: O(1) in both time and space.
 */
size_t num_different_bits_1(const uint32_t x, const uint32_t y)
{
    /*
     * each bit of z is set only if it the equivalent bits of x and y
     * are different, so the number of bits set to 1 in z is the answer
     * we want
     */
    uint32_t z = x ^ y;

    size_t count = 0;

    while (z > 0)
    {
        count += z % 2;
        z >>= 1;
    }

    return count;
}

/**
 * @brief Returns the number of bits in x which differ from y using a bitset.
 * @note Complexity: O(1) in both time and space (but this solution is better
 *       than the other one as it can use specialized machine instructions for
 *       counting the number of bits set on an integer value).
 */
size_t num_different_bits_2(const uint32_t x, const uint32_t y)
{
    return std::bitset<32>(x ^ y).count();
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<uint32_t> distribution;

    for (uint32_t i = 0; i < 1000000; ++i)
    {
        uint32_t x = distribution(generator);
        uint32_t y = distribution(generator);

        assert(num_different_bits_1(x, y) == num_different_bits_2(x, y));
    }

    std::cout << "passed random tests" << std::endl;

    return EXIT_SUCCESS;
}
