/*
 * TASK: For a given array of integers, determine the contiguous sequence with
 *       the largest sum and compute this sum. The array values may be both
 *       positive and negative.
 */

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief Computes the largest contiguous-sequence sum using brute force.
 * @note Complexity: O(n²) in time, O(1) in space.
 */
int sequence_largest_sum_1(const std::vector<int>& values)
{
    int max_sum = std::numeric_limits<int>::min();

    for (size_t i = 0; i < values.size(); ++i)
    {
        int sum = values[i];
        max_sum = std::max(sum, max_sum);

        for (size_t j = i + 1; j < values.size(); ++j)
        {
            sum += values[j];
            max_sum = std::max(sum, max_sum);
        }
    }

    return max_sum;
}

/**
 * @brief Computes the largest contiguous-sequence sum by integrating only over
 *        ranges which sum to nonnegative values.
 * @note Complexity: O(n) in time, O(1) in space.
 */
int sequence_largest_sum_2(const std::vector<int>& values)
{
    int max_sum = std::numeric_limits<int>::min();

    int current_sum = 0;

    for (size_t i = 0; i < values.size(); ++i)
    {
        current_sum += values[i];

        max_sum = std::max(max_sum, current_sum);

        if (current_sum < 0)
        {
            current_sum = 0;
        }
    }

    return max_sum;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-100, 100);

    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<int> values;

            while (values.size() < n)
            {
                values.push_back(distribution(generator));
            }

            assert(sequence_largest_sum_1(values) ==
                   sequence_largest_sum_2(values));
        }

        std::cout << "passed random tests for arrays of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
