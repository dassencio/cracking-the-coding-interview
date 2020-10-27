/*
 * TASK: You are given an initially sorted array of strings to which empty
 *       strings ("") were inserted at random positions. For instance, the array
 *       { "ape", "", "",  "bird", "cat", "",  "dog" } is an example of such an
 *       array. Given a string str, determine its position on the given array.
 *       To clarify, searching for "bird" on the array above should yield 3,
 *       while searching for "elephant" should yield some value which indicates
 *       it could not be found (e.g. the size of array).
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/**
 * @brief Returns the position of a string str on an array of strings or the
 *        size of the array if str could not be found.
 * @note Complexity: O(n) in time, O(1) in space, where n is the number of
 *       strings in the array (however, the complexity becomes O(log(n)) in
 *       time if the input array has no empty strings and str is not empty).
 */
size_t find(const std::vector<std::string>& strings, const std::string& str)
{
    if (strings.empty() == true)
    {
        return 0;
    }

    size_t left = 0;
    size_t right = strings.size() - 1;

    /* special case: if str == "", use linear search to find it */
    if (str == "")
    {
        size_t i = 0;

        while (i < strings.size() && strings[i] != "")
        {
            ++i;
        }

        return i;
    }

    /* at this point, we know that str != "" */
    while (left != right)
    {
        /* middle < right (always) */
        size_t middle = left + (right - left) / 2;

        /*
         * when strings[middle] == "", we cannot determine whether str
         * is to its right or to its left, so shrink the target range by
         * one and try again; otherwise use binary search to shrink the
         * target range by half
         */
        if (strings[middle] == "")
        {
            /*
             * if strings[left] == "", then the condition of the if
             * statement below is satisfied trivially since "" < str,
             * but if strings[left] != "" and strings[left] >= str,
             * then either we found str at left or str cannot be in
             * the array, i.e., we can stop searching
             */
            if (strings[left] < str)
            {
                ++left;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (strings[middle] < str)
            {
                left = middle + 1;
            }
            else
            {
                right = middle;
            }
        }
    }

    return (strings[left] == str) ? left : strings.size();
}

/**
 * @brief Generates a random ASCII string of random length in [1,10] with
 *        characters in [a-z].
 * @note Complexity: O(1) in both time and space.
 */
std::string random_string()
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<size_t> size_chooser(1, 10);
    std::uniform_int_distribution<char> letter_chooser('a', 'z');

    size_t size = size_chooser(generator);

    std::string str;

    while (str.size() < size)
    {
        str.push_back(letter_chooser(generator));
    }

    return str;
}

/**
 * @brief Generates a sorted array of random strings such that, on average, 70%
 *        of the strings will be empty ("") and the other 30% will be nonempty;
 *        the array is sorted in the sense that its nonempty strings are ordered
 *        lexicographically, but the empty strings are placed randomly
 *        throughout the array.
 * @note Complexity: O(n) in both time and space.
 */
std::vector<std::string> sorted_random_strings(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::vector<std::string> strings;

    /* generate n nonempty random strings */
    while (strings.size() < n)
    {
        strings.push_back(random_string());
    }

    /* sort the array of (nonempty) strings */
    std::sort(strings.begin(), strings.end());

    std::bernoulli_distribution empty_string(0.7);

    /* replace 70% of the strings with "" (on average) */
    for (std::string& str : strings)
    {
        if (empty_string(generator) == true)
        {
            str = "";
        }
    }

    return strings;
}

int main()
{
    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 100; ++i)
        {
            std::vector<std::string> strings = sorted_random_strings(n);

            for (const std::string& str : strings)
            {
                assert(strings[find(strings, str)] == str);
            }

            /* search for some random strings not in the array as well */
            for (int k = 0; k < 100; ++k)
            {
                std::string str = random_string();

                auto it = std::find(strings.begin(), strings.end(), str);

                if (it != strings.end())
                {
                    assert(strings[find(strings, str)] == str);
                }
                else
                {
                    assert(find(strings, str) == strings.size());
                }
            }
        }

        std::cout << "passed random tests for arrays of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
