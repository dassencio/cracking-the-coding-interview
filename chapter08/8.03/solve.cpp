/*
 * TASK: Determine all subsets of a given set.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using subsets = std::vector<std::vector<size_t> >;

/**
 * @brief Computes all subsets of a set recursively.
 * @param values An array containing the values in the set.
 * @param i An index such that subsets will be built only from elements of
 *        values with indices in [i,n), where n is the number of elements in the
 *        set.
 * @return An array holding all subsets of the given set (with indices >= i).
 * @note Complexity: O(n*2^n) in both time and space, because the total number
 *       of subsets is 2^n and each subset has size O(n).
 */
subsets all_subsets_1(const std::vector<size_t>& values, const size_t i = 0)
{
    /* base case: we are one past the last element of the input set */
    if (i == values.size())
    {
        /* the empty set is also a valid subset */
        return {{}};
    }

    subsets sets = all_subsets_1(values, i + 1);

    subsets __sets = sets;

    /*
     * go over each set obtained so far and generate a copy which also
     * contains values[i]
     */
    for (std::vector<size_t>& s : __sets)
    {
        s.push_back(values[i]);
    }

    std::move(__sets.begin(), __sets.end(), std::back_inserter(sets));

    return sets;
}

/**
 * @brief Computes all subsets of a set iteratively.
 * @param values An array containing the values in the set.
 * @return An array holding all subsets of the given set.
 * @note Complexity: O(n*2^n) in both time and space, where n is the number of
 *       elements in the set, because the total number of subsets is 2^n and
 *       each subset has size O(n).
 */
subsets all_subsets_2(const std::vector<size_t>& values)
{
    size_t i = 0;

    subsets sets = {{}};

    while (i < values.size())
    {
        subsets __sets = sets;

        /*
         * go over each set obtained so far and generate a copy which
         * also contains values[i]
         */
        for (std::vector<size_t>& S : __sets)
        {
            S.push_back(values[i]);
        }

        std::move(__sets.begin(), __sets.end(), std::back_inserter(sets));

        ++i;
    }

    return sets;
}

/**
 * @brief Returns true if two set of subsets are equal, false otherwise.
 * @note Complexity: O(2^n*n*log(n)) in time, O(1) in space, where n is the
 *       number of elements in the original set from which U and V were built.
 */
bool sets_are_equal(subsets U, subsets V)
{
    for (std::vector<size_t>& u : U)
    {
        std::sort(u.begin(), u.end());
    }

    for (std::vector<size_t>& v : V)
    {
        std::sort(v.begin(), v.end());
    }

    std::sort(U.begin(), U.end());
    std::sort(V.begin(), V.end());

    return U == V;
}

int main()
{
    for (size_t n = 0; n <= 15; ++n)
    {
        std::vector<size_t> values;

        for (size_t i = 0; i < n; ++i)
        {
            values.push_back(i);
        }

        subsets U = all_subsets_1(values);
        subsets V = all_subsets_2(values);

        assert(U.size() == std::pow(2, n));
        assert(V.size() == std::pow(2, n));

        assert(sets_are_equal(U, V) == true);

        std::cout << "passed test for set with size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
