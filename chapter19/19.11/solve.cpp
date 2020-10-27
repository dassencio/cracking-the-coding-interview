/*
 * TASK: Given an array of integers and an integer t, determine all the unique
 *       pairs of integers in the input array which sum to t.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using int_pair = std::pair<int, int>;

/**
 * @brief Returns an array containing all unique pairs of integers in v which
 *        sum to t using a hash set.
 * @note Complexity: O(n) in both time and space, where n is the size of v.
 */
std::vector<int_pair> two_sum_1(const std::vector<int>& v, const int t)
{
    /* keep only one copy of each unique value in v in O(n) time */
    std::unordered_set<int> values(v.begin(), v.end());

    std::vector<int_pair> pairs;

    for (const int x : values)
    {
        /* avoid a pair (a,b) from appearing a second time as (b,a) */
        if (t - x < x)
        {
            continue;
        }

        if (values.find(t - x) != values.end())
        {
            pairs.push_back({x, t - x});
        }
    }

    return pairs;
}

/**
 * @brief Returns an array containing all unique pairs of integers in v which
 *        sum to t by first sorting v and using binary search to find the pairs.
 * @note Complexity: O(n*log(n)) in time, O(n) in space, where n is the size of
 *       v.
 */
std::vector<int_pair> two_sum_2(std::vector<int> v, const int t)
{
    std::sort(v.begin(), v.end());

    /* keep only one copy of each unique value in v in O(n) time */
    v.erase(std::unique(v.begin(), v.end()), v.end());

    std::vector<int_pair> pairs;

    for (const int x : v)
    {
        /* avoid a pair (a,b) from appearing a second time as (b,a) */
        if (t - x < x)
        {
            break;
        }

        /*
         * we could slightly optimize this function by using iterators
         * to go over the elements in v and then doing the binary search
         * only over elements to the right and including the current one
         * being looked at; this is fine since we never consider pairs
         * of elements (v[i],v[j]) for j < i because such a pair will
         * have already been found earlier as (v[j],v[i])
         */
        if (std::binary_search(v.begin(), v.end(), t - x) == true)
        {
            pairs.push_back({x, t - x});
        }
    }

    return pairs;
}

/**
 * @brief Returns a random vector containing n values in [-100,100].
 * @note Complexity: O(n) in both time and space.
 */
std::vector<int> random_vector(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-100, 100);

    std::vector<int> v;

    while (v.size() < n)
    {
        v.push_back(distribution(generator));
    }

    return v;
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        std::vector<int> v = random_vector(n);

        /*
         * since v has only values in [-100,100], the sum of any
         * pair of elements in v must be in [-200,200]
         */
        for (int t = -250; t <= 250; ++t)
        {
            std::vector<int_pair> pairs_1 = two_sum_1(v, t);
            std::vector<int_pair> pairs_2 = two_sum_2(v, t);

            std::sort(pairs_1.begin(), pairs_1.end());

            assert(pairs_1 == pairs_2);

            for (auto p : pairs_1)
            {
                assert(p.first + p.second == t);
            }
        }

        std::cout << "passed random test for array of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
