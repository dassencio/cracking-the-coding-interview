/*
 * TASK: You are given two strings. Determine if one is a rotation of the other.
 *       As an example, given a string "abcde", its possible rotations are
 *       "abcde" (no rotation), "bcdea", "cdeab", "deabc" and "eabcd". You are
 *       allowed to determine if one string is a substring of the other (e.g.
 *       using std::find) at most once.
 */

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>

/**
 * @brief Solution which checks if str2 appears in (str1 + str1).
 * @return true if str2 is a rotation of str1, false otherwise.
 * @note Complexity: O(n) in both time and space, where n is the length of
 *       the strings (if not the same, one cannot be a rotation of the other).
 */
bool is_rotation_1(const std::string& str1, const std::string& str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }

    return (str1 + str1).find(str2) != std::string::npos;
}

/**
 * @brief Brute-force solution: compares str2 with all rotations of str1.
 * @return true if str2 is a rotation of str1, false otherwise.
 * @note Complexity: O(n²) in time, O(n) in space, where n is the length of
 *       the strings (if not the same, one cannot be a rotation of the other).
 */
bool is_rotation_2(std::string str1, const std::string& str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }

    bool result = (str1 == str2);

    for (size_t j = 0; j + 1 < str1.size() && result == false; ++j)
    {
        std::rotate(str1.begin(), str1.begin() + 1, str1.end());

        result = (str1 == str2);
    }

    return result;
}

/**
 * @brief Generates a random ASCII string of length n and characters in [a-c].
 * @note Complexity: O(n) in both time and space.
 */
std::string random_string(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<char> distribution('a', 'c');

    std::string str;

    while (str.size() < n)
    {
        str.push_back(distribution(generator));
    }

    return str;
}

int main()
{
    for (size_t n = 0; n <= 20; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::string str1 = random_string(n);
            std::string str2 = random_string(n);

            assert(is_rotation_1(str1, str2) == is_rotation_2(str1, str2));

            for (size_t j = 0; j < n; ++j)
            {
                std::string str1_rot = str1;
                std::rotate(
                    str1_rot.begin(), str1_rot.begin() + j, str1_rot.end());

                assert(is_rotation_1(str1, str1_rot) == true);
                assert(is_rotation_2(str1, str1_rot) == true);
            }
        }

        std::cout << "passed random tests for strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
