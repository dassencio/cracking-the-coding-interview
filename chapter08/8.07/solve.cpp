/*
 * TASK: Determine all possible ways in which one can pay n cents using only
 *       coins of values 1, 5, 10 and 25 cents. For example, if n = 12, we can
 *       pay using any of the coin combinations below:
 *
 *       12 × 1 cent
 *       (7 × 1 cent) + (1 × 5 cent)
 *       (2 × 1 cent) + (2 × 5 cent)
 *       (2 × 1 cent) + (1 × 10 cent)
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using coin_sequence = std::vector<int>;

/**
 * @brief Returns an array containing all possible sequences of 1 cent, 5 cent,
 *        10 cent and 25 cent coins which add to n, with each such sequence
 *        stored as an array of coin values.
 */
std::vector<coin_sequence> represent_cents(const int n,
                                           const size_t coin_index = 0)
{
    static const std::array<int, 4> valid_coins = {1, 5, 10, 25};

    /* if we have not reached a valid solution */
    if (coin_index == valid_coins.size())
    {
        return {};
    }

    /* base case: no coins needed to represent n */
    if (n == 0)
    {
        return {{}};
    }

    std::vector<coin_sequence> seqs;

    const int coin = valid_coins[coin_index];

    /*
     * try to fit in as many of 'coin' as possible and solve the problem
     * recursively for each possibility
     */
    for (int k = 0; k * coin <= n; ++k)
    {
        std::vector<coin_sequence> __seqs =
            represent_cents(n - k * coin, coin_index + 1);

        /* insert 'coin' k times on each sequence of __seqs */
        for (coin_sequence& seq : __seqs)
        {
            std::fill_n(std::back_inserter(seq), k, coin);
        }

        std::move(__seqs.begin(), __seqs.end(), std::back_inserter(seqs));
    }

    return seqs;
}

int main()
{
    for (int n = 0; n <= 100; ++n)
    {
        std::vector<coin_sequence> seqs = represent_cents(n);

        for (const coin_sequence& seq : seqs)
        {
            assert(std::accumulate(seq.begin(), seq.end(), 0) == n);
        }

        std::cout << "passed test for " << n << " cents" << std::endl;
    }

    return EXIT_SUCCESS;
}
