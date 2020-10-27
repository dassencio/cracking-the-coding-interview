/*
 * TASK: Given two strings, determine if they are anagrams. Two strings are
 *       said to be anagrams if they contains exactly the same characters (but
 *       not necessarily in the same order).
 *
 */

#include <algorithm> /* std::sort, std::shuffle */
#include <cassert>
#include <iostream>
#include <random>
#include <string>

/**
 * @brief Solution using sorting.
 * @return true if str1 and str2 are anagrams, false otherwise.
 * @note Complexity: O(n*log(n)) in time, O(n) in space (but can be O(1) in
 *       space if we don't mind losing the original strings since we can sort
 *       them in place instead of sorting copies of them), where n is the
 *       length of the longest string.
 */
bool is_anagram_1(std::string str1, std::string str2)
{
    std::sort(str1.begin(), str1.end());
    std::sort(str2.begin(), str2.end());

    return (str1 == str2);
}

/**
 * @brief Solution using counters for each character (the input strings are
 *        allowed to contain any valid ASCII characters).
 * @return true if str1 and str2 are anagrams, false otherwise.
 * @note Complexity: O(n) in time, O(1) in space but needs to use a somewhat
 *       large array (128 integers corresponding to each possible character),
 *       where n is the length of the longest string.
 */
bool is_anagram_2(const std::string& str1, const std::string& str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }

    size_t chars_count[128]{};

    for (size_t i = 0; i < str1.size(); ++i)
    {
        ++chars_count[static_cast<int>(str1[i])];
    }

    for (size_t i = 0; i < str2.size(); ++i)
    {
        /* if we're finding a new character or if str2 has more of
         * a given character than str1 */
        if (chars_count[static_cast<int>(str2[i])] == 0)
        {
            return false;
        }
        --chars_count[static_cast<int>(str2[i])];
    }

    for (auto n : chars_count)
    {
        if (n != 0)
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Generates a random ASCII string of length n.
 * @note Complexity: O(n) in both time and space.
 */
std::string random_string(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<char> distribution(0, 127);

    std::string str;

    while (str.size() < n)
    {
        str.push_back(distribution(generator));
    }

    return str;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::string str1 = random_string(n);
            std::string str2 = random_string(n);

            assert(is_anagram_1(str1, str2) == is_anagram_2(str1, str2));

            std::string str1_shuf = str1;
            std::shuffle(str1_shuf.begin(), str1_shuf.end(), generator);

            assert(is_anagram_1(str1, str1_shuf) == true);
            assert(is_anagram_2(str1, str1_shuf) == true);
        }

        std::cout << "passed random tests for strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
