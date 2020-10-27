/*
 * TASK: Determine all the permutations of a given string.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/**
 * @brief Computes all possible permutations of an input string.
 * @param str An input string.
 * @param i An index such that permutations will be built only for the substring
 *        str[i..n), where n is the length of str.
 * @return An array holding all permutations of str[i..n).
 * @note Complexity: O((n-i+1)!) in both time and space because each permutation
 *       is itself a string of length n-i and there are (n-i)! permutations in
 *       total for str[i..n).
 */
std::vector<std::string> compute_permutations(const std::string& str,
                                              const size_t i = 0)
{
    /* base case: we are one past the last character of str */
    if (i == str.size())
    {
        return {""};
    }

    std::vector<std::string> sub_permutations =
        compute_permutations(str, i + 1);

    std::vector<std::string> permutations;

    /*
     * go over each permutation of str[i+1..n) and generate copies of it
     * with str[i] placed on every valid position; this gives us then all
     * permutations of str[i..n)
     */
    for (const std::string& s : sub_permutations)
    {
        for (size_t k = 0; k <= s.size(); ++k)
        {
            permutations.emplace_back(s.substr(0, k) + str[i] + s.substr(k));
        }
    }

    return permutations;
}

/**
 * @brief Returns n!.
 */
size_t factorial(const size_t n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

/**
 * @brief Generates a string containing the first n letters of the alphabet
 *        or the entire alphabet if n > 26.
 */
std::string alphabet(const size_t n)
{
    static std::string letters = "abcdefghijklmnopqrstuvwxyz";

    return letters.substr(0, n);
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    for (size_t n = 0; n <= 10; ++n)
    {
        std::string str = alphabet(n);

        std::vector<std::string> permutations = compute_permutations(str);

        assert(permutations.size() == factorial(n));

        /* check if some random permutations of str were generated */
        for (int i = 0; i < 100; ++i)
        {
            std::shuffle(str.begin(), str.end(), generator);

            auto it = std::find(permutations.begin(), permutations.end(), str);
            assert(it != permutations.end());
        }

        std::cout << "passed random tests for strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
