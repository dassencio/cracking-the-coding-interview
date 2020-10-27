/*
 * TASK: Given an array of non-empty strings, determine its longest string
 *       which is the concatenation of some pair of strings in this array. As an
 *       example, in { "dog", "cat", "dogcat", "elephant", "elephantdog" },
 *       the result would be "elephantdog".
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/**
 * @brief Determines the longest string in an array of strings v which is the
 *        concatenation of some pair of strings in v using brute force; if no
 *        such string exists, returns an empty string.
 * @note Complexity: O(n³*d) in time, O(d) in space, where n is the size of
 *       v and d is the length of its longest string.
 */
std::string longest_concatenated_string_1(const std::vector<std::string>& v)
{
    std::string longest;

    for (const std::string& s : v)
    {
        /*
         * compare s against s1 + s2 for all pairs of strings (s1,s2)
         * such that s1 and s2 are in v
         */
        for (const std::string& s1 : v)
        {
            for (const std::string& s2 : v)
            {
                if (s == s1 + s2 && s.size() > longest.size())
                {
                    longest = s;
                }
            }
        }
    }

    return longest;
}

/**
 * @brief Determines the longest string in an array of strings v which is the
 *        concatenation of some pair of strings in v by first sorting v to
 *        optimize string searches; if no such string exists, returns an empty
 *        string.
 * @note Complexity: O(n*d*log(n)) in time, O(n*d) in space, where n is the size
 *       of v and d is the length of its longest string.
 */
std::string longest_concatenated_string_2(std::vector<std::string> v)
{
    /* sorting v takes O(n*d*log(n)) time */
    std::sort(v.begin(), v.end());

    std::string longest;

    for (const std::string& s : v)
    {
        /*
         * consider all non-empty substrings s[0,i) and s[i,...), then
         * determine if these strings appear in v; since v is sorted,
         * we can use binary search to optimize the searches
         */
        for (size_t i = 1; i < s.size(); ++i)
        {
            std::string s1 = s.substr(0, i);
            std::string s2 = s.substr(i, std::string::npos);

            bool s1_found = std::binary_search(v.begin(), v.end(), s1);

            if (s1_found == false)
            {
                continue;
            }

            bool s2_found = std::binary_search(v.begin(), v.end(), s2);

            if (s2_found == true)
            {
                if (s.size() > longest.size())
                {
                    longest = s;
                }
            }
        }
    }

    return longest;
}

/**
 * @brief Generates a vector of random ASCII strings of random length in [1,5]
 *        with characters in [a-c].
 * @note Complexity: O(n) in both time and space.
 */
std::vector<std::string> random_strings(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<size_t> size_chooser(1, 5);
    std::uniform_int_distribution<char> letter_chooser('a', 'c');

    std::vector<std::string> v;

    while (v.size() < n)
    {
        size_t size = size_chooser(generator);

        std::string str;

        while (str.size() < size)
        {
            str.push_back(letter_chooser(generator));
        }

        v.push_back(str);
    }

    return v;
}

int main()
{
    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 100; ++i)
        {
            std::vector<std::string> v = random_strings(n);

            std::string s1 = longest_concatenated_string_1(v);
            std::string s2 = longest_concatenated_string_2(v);

            if (s1 != "")
            {
                assert(std::find(v.begin(), v.end(), s1) != v.end());
            }

            if (s2 != "")
            {
                assert(std::find(v.begin(), v.end(), s2) != v.end());
            }

            assert(s1.size() == s2.size());
        }

        std::cout << "passed random tests for arrays of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
