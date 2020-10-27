/*
 * TASK: Given an array of strings, sort them in a way which groups anagrams
 *       together. As an example, given { "abc", "def", "bca", "fed", "ace" },
 *       the result will be { "abc", "bca", "ace", "def", "fed" }.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/**
 * @brief Compare function which yields the following string order: anagrams
 *        are grouped together and ordered (as blocks) using the unique
 *        lexicographically sorted version of its strings, and anagram groups
 *        are themselves ordered internally using the lexicographical order of
 *        their strings.
 * @note Complexity: O(n*log(n)) in time, O(n) in space, where n is the length
 *       of the longest string.
 */
bool anagram_compare(const std::string& s1, const std::string& s2)
{
    std::string s1_sorted = s1;
    std::string s2_sorted = s2;

    std::sort(s1_sorted.begin(), s1_sorted.end());
    std::sort(s2_sorted.begin(), s2_sorted.end());

    /* if s1 and s2 are anagrams */
    if (s1_sorted == s2_sorted)
    {
        /* sort also among anagrams */
        return s1 < s2;
    }
    else
    {
        /* keep anagrams together in groups */
        return s1_sorted < s2_sorted;
    }
}

/**
 * @brief Sorts an array of strings in a way which groups anagrams together.
 * @note Complexity: O(m*n*log(m)*log(n)) in time, O(n) in space, where m is
 *       the number of strings in the array and n is the length of its longest
 *       string.
 */
void anagram_sort(std::vector<std::string>& strings)
{
    std::sort(strings.begin(), strings.end(), anagram_compare);
}

int main()
{
    /* original string arrays already sorted in the desired order */
    std::vector<std::vector<std::string> > original = {
        {},
        {""},
        {"a"},
        {"", "a"},
        {"a", "a"},
        {"a", "b"},
        {"a", "a", "b"},
        {"a", "a", "b", "b"},
        {"a", "a", "b", "bb"},
        {"a", "ab", "ba", "b"},
        {"a", "ac", "ca", "b"},
        {"a", "a", "b", "bb", "c"},
        {"abc", "acb", "bac", "bca", "cab", "cba"},
        {"abc", "acb", "bac", "bca", "def", "fde", "fed"},
    };

    std::random_device device;
    std::mt19937 generator(device());

    for (size_t n = 0; n < original.size(); ++n)
    {
        std::vector<std::string> strings = original[n];

        /*
         * shuffle the array many times and sort it again, then see if
         * we obtain the original order
         */
        for (int i = 0; i < 10; ++i)
        {
            std::shuffle(strings.begin(), strings.end(), generator);

            anagram_sort(strings);
            assert(strings == original[n]);
        }

        std::cout << "passed random tests for array " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
