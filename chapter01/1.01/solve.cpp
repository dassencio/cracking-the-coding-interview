/*
 * TASK: Given a string, determine if each of its characters is unique, i.e.,
 *       whether the string has duplicate characters or not. Try solving this
 *       problem without using any additional data structures (such as a
 *       buffer).
 */

#include <algorithm> /* std::sort */
#include <cassert>
#include <iostream>
#include <random>
#include <string>

/**
 * @brief Solution using a bitmask to mark the seen characters.
 * @return true if the input string has duplicate characters, false otherwise.
 * @note Complexity: O(n) in time, O(1) in space, where n is the string length.
 * @note This implementation assumes all characters are in the range [a-z].
 */
bool has_duplicates_1(const std::string& str)
{
    unsigned int chars_seen = 0;

    for (const char c : str)
    {
        /* if the character c has already been seen */
        if (chars_seen & (1 << (c - 'a')))
        {
            return true;
        }
        chars_seen |= 1 << (c - 'a');
    }

    return false;
}

/**
 * @brief Solution without using any additional data structures.
 * @return true if the input string has duplicate characters, false otherwise.
 * @note Complexity: O(n*log(n)) in time, O(n) in space (but can be O(1) in
 *       space if we don't mind losing the original string str since we can
 *       sort it in place instead of sorting a copy of it), where n is the
 *       string length.
 */
bool has_duplicates_2(std::string str)
{
    std::sort(str.begin(), str.end());

    /* detect duplicate characters */
    for (size_t i = 0; i + 1 < str.size(); ++i)
    {
        if (str[i] == str[i + 1])
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Brute-force solution: check all characters against each other.
 * @return true if the input string has duplicate characters, false otherwise.
 * @note Complexity: O(n²) in time, O(1) in space, where n is the string length.
 */
bool has_duplicates_3(const std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        for (size_t j = i + 1; j < str.size(); ++j)
        {
            if (str[i] == str[j])
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Generates a random string of length n and characters in [a-z].
 * @note Complexity: O(n) in both time and space.
 */
std::string random_string(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<char> distribution('a', 'z');

    std::string str;

    while (str.size() < n)
    {
        str.push_back(distribution(generator));
    }

    return str;
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::string str = random_string(n);

            bool result = has_duplicates_3(str);

            assert(has_duplicates_1(str) == result);
            assert(has_duplicates_2(str) == result);
        }

        std::cout << "passed random tests for strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
