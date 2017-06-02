/*
 * TASK: Determine all properly opened and closed combinations of n pairs of
 *       parentheses. As an example, for n = 3, the valid combinations are:
 *
 *       ((()))
 *       (()())
 *       (())()
 *       ()(())
 *       ()()()
 *
 * NOTE: A parentheses string is valid if, when read from left to right, the
 *      number of opening parentheses '(' is always less than or equal to the
 *      number of closing parentheses ')', and if both appear the same number
 *      of times in the string.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> __generate_parentheses(const size_t open,
                                                const size_t close)
{
    /*
     * open must always be smaller than or equal to close, otherwise we
     * have closed more parentheses than we have opened already
     */

    /* base case: we are closing the last open parenthesis */
    if (open == 0 && close == 1)
    {
        return {")"};
    }

    std::vector<std::string> parentheses;

    /* if we can open a parenthesis */
    if (open > 0)
    {
        std::vector<std::string> open_par =
            __generate_parentheses(open - 1, close);

        for (const std::string& str : open_par)
        {
            parentheses.emplace_back('(' + str);
        }
    }

    /* if we can close a parenthesis */
    if (open < close)
    {
        std::vector<std::string> close_par =
            __generate_parentheses(open, close - 1);

        for (const std::string& str : close_par)
        {
            parentheses.emplace_back(')' + str);
        }
    }

    return parentheses;
}

/**
 * @brief Generates an array with all valid parentheses strings containing
 *        n pairs of parentheses.
 * @note Complexity: O((2n)!/(n!*(n-1)!)) in both time and space since the
 *       number of possible strings generated with n '('s and n ')'s is
 *       (2n)!/(n!*n!) and each generated string has length n.
 */
std::vector<std::string> generate_parentheses(const size_t n)
{
    if (n == 0)
    {
        return {""};
    }

    return __generate_parentheses(n, n);
}

/**
 * @brief Returns true if a string is a valid parentheses string, false
 *        otherwise.
 * @note Complexity: O(m), where m is the string length.
 */
bool is_valid_string(const std::string& str)
{
    /* a string with an odd number of characters cannot be valid */
    if (str.size() % 2 != 0)
    {
        return false;
    }

    /* open and close count the number of '('s and ')'s respectively */
    size_t open = 0;
    size_t close = 0;

    for (const char c : str)
    {
        open += (c == '(');
        close += (c == ')');

        /*
         * if we are closing a parenthesis we have not opened, the
         * solution is invalid
         */
        if (close > open)
        {
            return false;
        }
    }

    size_t n = str.size() / 2;

    if (open != n || close != n)
    {
        return false;
    }

    return true;
}

int main()
{
    for (size_t n = 0; n <= 10; ++n)
    {
        std::vector<std::string> parentheses = generate_parentheses(n);

        for (const std::string& str : parentheses)
        {
            assert(is_valid_string(str) == true);
        }

        std::cout << "passed tests for parentheses strings of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
