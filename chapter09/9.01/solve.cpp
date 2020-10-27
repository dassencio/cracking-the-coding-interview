/*
 * TASK: Given two sorted arrays v1 and v2, merge their values while keeping
 *       them sorted. The final result should be placed into v1 (v1 is assumed
 *       to initially have enough space to accommodate the values of v2 as
 *       well).
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief Merges the values of two sorted arrays v1 and v2 on top of v1.
 * @note Complexity: O(n) in time, O(1) in space, where n = n1 + n2 is the sum
 *       of the lengths n1 and n2 of v1 and v2 respectively (the last n2
 *       elements of v1 are not merged as they are assumed to be merely buffer
 *       space for the merging with v2).
 * @note The trick used here is the fact that the values of v1 and v2 can be
 *       merged in descending order, i.e., we merge from right to left.
 */
void merge(std::vector<int>& v1, const std::vector<int>& v2)
{
    /* one past the rightmost unmerged element of v1 */
    size_t i1 = v1.size() - v2.size();

    /* one past the rightmost unmerged element of v2 */
    size_t i2 = v2.size();

    /* one past the slot for the next element that will be merged */
    size_t i = v1.size();

    /* insert the largest of v1[i1-1] and v2[i2-1] into v1[i-1] */
    while (i1 > 0 && i2 > 0)
    {
        if (v1[i1 - 1] >= v2[i2 - 1])
        {
            --i1;
            --i;
            v1[i] = v1[i1];
        }
        else
        {
            --i2;
            --i;
            v1[i] = v2[i2];
        }
    }

    /*
     * if all elements of v1 have been merged, but not all of v2, then copy
     * the missing ones directly into the leftmost unused slots of v1; we do
     * not need an equivalent loop for the elements of v1 as in that case
     * they are already in their correct places
     */
    while (i2 > 0)
    {
        --i2;
        --i;
        v1[i] = v2[i2];
    }
}

/**
 * @brief Generates a sorted random vector of length n.
 * @note Complexity: O(n*log(n)) in time, O(n) in space.
 */
std::vector<int> sorted_random_vector(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution;

    std::vector<int> values;

    while (values.size() < n)
    {
        values.push_back(distribution(generator));
    }

    std::sort(values.begin(), values.end());

    return values;
}

int main()
{
    size_t max_size = 10;

    for (size_t n1 = 0; n1 <= max_size; ++n1)
    {
        for (size_t n2 = 0; n2 <= max_size; ++n2)
        {
            for (int i = 0; i < 1000; ++i)
            {
                std::vector<int> v1 = sorted_random_vector(n1);
                std::vector<int> v2 = sorted_random_vector(n2);

                std::vector<int> values;
                std::merge(v1.begin(),
                           v1.end(),
                           v2.begin(),
                           v2.end(),
                           std::back_inserter(values));

                /* add a buffer at the end of v1 with the size of v2 */
                v1.resize(v1.size() + v2.size());

                merge(v1, v2);

                assert(v1 == values);
            }

            std::cout << "passed random tests for arrays of sizes " << n1
                      << " and " << n2 << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
