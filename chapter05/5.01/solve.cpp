/*
 * TASK: For two given 32-bit numbers N and M, with N = [n_0,...,n_31] being
 *       such that n_k is the k-th bit of N (k = 0 is the LSB of N, k = 31 is
 *       its MSB) and similar for M, copy the bits [m_0,...,m_(j-i)] of M to
 *       the bits [m_i,...,m_j] of N, where 0 <= i <= j and 0 <= j <= 31. As an
 *       example, if N = 1000000, M = 100011, i = 3 and j = 5, then N becomes
 *       1011000.
 *
 * NOTE: The problem solved here is slightly more general than the original one
 *       because M is not assumed to have length (j-i).
 */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief Returns true if the bits [m_0,...,m_(j-i)] of M are equal to the bits
 *        [n_i,...,n_j] of N, false otherwise.
 */
bool is_substring(const uint32_t N,
                  const uint32_t M,
                  const uint8_t i,
                  const uint8_t j)
{
    std::bitset<32> N_bits(N);
    std::bitset<32> M_bits(M);

    for (uint8_t k = i; k <= j; ++k)
    {
        if (N_bits[k] != M_bits[k - i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<uint32_t> distribution;

    for (uint8_t i = 0; i <= 31; ++i)
    {
        for (uint8_t j = i; j <= 31; ++j)
        {
            for (int k = 0; k < 1000; ++k)
            {
                uint32_t N = distribution(generator);
                uint32_t M = distribution(generator);

                /*
                 * create a mask with only the bits [0,...,j-i]
                 * equal to 1 (j-i+1 == 32 happens only if i = 0
                 * and j = 31, in which case we are effectively
                 * copying all bits from M to N)
                 */
                uint32_t mask =
                    (j - i + 1 < 32) ? ((1 << (j - i + 1)) - 1) : ~0;

                /*
                 * make the bits [n_i,...,n_j] of N equal to the
                 * bits [m_0,...,m_(j-i)] of M
                 */
                N = (N & ~(mask << i)) + ((M & mask) << i);

                assert(is_substring(N, M, i, j) == true);
            }

            std::cout << "passed random tests for (i,j) = "
                      << static_cast<int>(i) << "," << static_cast<int>(j)
                      << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
