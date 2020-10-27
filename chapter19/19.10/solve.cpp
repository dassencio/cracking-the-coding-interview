/*
 * TASK: Given a method rand5() which generates random integers uniformly in
 *       [1,5], create another method rand7() which generates random integers
 *       uniformly in [1,7].
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief Generates random integers uniformly in [1,5].
 * @note Complexity: O(1) in both time and space.
 */
int rand5()
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(1, 5);

    return distribution(generator);
}

/**
 * @brief Generates random integers uniformly in [1,7].
 * @note Complexity: O(1) in both time (on average) and space.
 */
int rand7()
{
    int result = 0;

    while (result < 1 || result > 7)
    {
        /* r1 is a random integer in [0,4] */
        int r1 = rand5() - 1;

        /*
         * only accept r1 if it has no bits set besides possibly the
         * two least significant ones (3 = 0b11)
         */
        if ((r1 & 3) != r1)
        {
            continue;
        }

        /* r2 is a random integer in [0,4] */
        int r2 = rand5() - 1;

        /*
         * only accept r2 if it has no bits set besides possibly the
         * two least significant ones (3 = 0b11)
         */
        if ((r2 & 3) != r2)
        {
            continue;
        }

        /* keep only the least significant bit of r2 */
        r2 &= 1;

        /*
         * at this point, we can use r1 and r2 to generate a random
         * number in [0,7], i.e., a number which can only have any of
         * its three lowest significant bits set, and take this number
         * as the final result only if it falls in [1,7]
         */
        result = r1 + (r2 << 2);
    }

    return result;
}

int main()
{
    const size_t samples = 100000;

    std::vector<int> count(7);

    for (size_t n = 0; n < samples; ++n)
    {
        int x = rand7();
        assert(1 <= x && x <= 7);

        ++count[x - 1];
    }

    std::cout << "frequency distribution (%) for rand7():\n";

    for (int i = 0; i < 7; ++i)
    {
        std::cout << i + 1 << ": " << (100.0 * count[i]) / samples << "\n";
    }

    return EXIT_SUCCESS;
}
