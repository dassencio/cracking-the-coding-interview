/*
 * TASK: Given two integers a and b, determine which one is the largest without
 *       using any comparison operators and no if/else statements.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief Returns the largest of two numbers a and b.
 * @note Complexity: O(1) in both time and space.
 */
int32_t max(const int32_t a, const int32_t b)
{
    int32_t sign_bit = ((a - b) >> 31) & 1;

    return a + sign_bit * (b - a);
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<int32_t> distribution(-1000, 1000);

    for (uint32_t i = 0; i < 1000000; ++i)
    {
        int32_t a = distribution(generator);
        int32_t b = distribution(generator);

        assert(max(a, b) == std::max(a, b));
    }

    std::cout << "passed all random tests" << std::endl;

    return EXIT_SUCCESS;
}
