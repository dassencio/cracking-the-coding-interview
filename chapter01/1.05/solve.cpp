/*
 * TASK: Given a string, replace all occurrences of the space character ' '
 *       on this string with the string "%20".
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>

/**
 * @brief Replaces spaces with "%20" on a string without using an extra buffer.
 * @note Complexity: O(n) in both time and space, where n is the string length.
 */
void replace_spaces_1(std::string& str)
{
    size_t spaces = std::count(str.begin(), str.end(), ' ');

    size_t j = str.size();

    /* ' ' -> "%20" adds two characters per space */
    str.resize(str.size() + 2 * spaces);

    for (size_t i = str.size(); j > 0; --j)
    {
        if (str[j - 1] == ' ')
        {
            str[i - 1] = '0';
            str[i - 2] = '2';
            str[i - 3] = '%';
            i -= 3;
        }
        else
        {
            str[i - 1] = str[j - 1];
            --i;
        }
    }
}

/**
 * @brief Replaces spaces with "%20" on a string using an extra buffer.
 * @note Complexity: O(n) in both time and space, where n is the string length.
 */
void replace_spaces_2(std::string& str)
{
    std::string result;

    for (char c : str)
    {
        if (c == ' ')
        {
            result += "%20";
        }
        else
        {
            result.push_back(c);
        }
    }

    str.swap(result);
}

/**
 * @brief Generates a random string of length n and characters in [a-d ], i.e.,
 *        { 'a', 'b', 'c', 'd', ' ' }.
 * @note Complexity: O(n) in both time and space.
 */
std::string random_string(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    char chars[] = "abcd ";

    std::uniform_int_distribution<size_t> distribution(0, 4);

    std::string str;

    while (str.size() < n)
    {
        str.push_back(chars[distribution(generator)]);
    }

    return str;
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::string str1 = random_string(n);
            std::string str2 = str1;

            replace_spaces_1(str1);
            replace_spaces_2(str2);

            assert(str1 == str2);
        }

        std::cout << "passed random tests for strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
