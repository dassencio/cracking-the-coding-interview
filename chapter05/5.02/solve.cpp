/*
 * TASK: Determine the binary representation of a decimal number represented as
 *       string (e.g. "1.25"). As an example, the binary representation of
 *       "1.25" is "1.01".
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>

/**
 * @brief Converts a string holding a nonnegative number in the decimal
 *        representation to a string holding its binary representation.
 * @note Complexity: O(1) in both time and space since the generated string
 *       will never exceed 64 characters in total (including the dot character).
 * @note This function will not yield accurate results for very large (e.g.
 *       > 1e10) or very small (e.g. < 1e-10) numbers.
 */
std::string to_binary_string(const std::string& dec_str)
{
    double dec_num = std::atof(dec_str.c_str());

    /* integer and fractionary part of dec_num */
    int64_t int_part = static_cast<int64_t>(dec_num);
    double frac_part = dec_num - static_cast<double>(int_part);

    std::string bin_str;

    /* process the integer part of dec_num */
    if (int_part == 0)
    {
        bin_str = '0';
    }
    while (int_part > 0)
    {
        char bin_digit = '0' + (int_part % 2);
        bin_str = bin_digit + bin_str;
        int_part /= 2;
    }

    bin_str += '.';

    /* process the fractionary part of dec_num */
    if (frac_part == 0.0)
    {
        bin_str += '0';
    }
    while (frac_part > 0.0)
    {
        frac_part *= 2.0;

        int8_t dec_digit = static_cast<int8_t>(frac_part);
        assert(0 <= dec_digit && dec_digit <= 9);

        char bin_digit = '0' + dec_digit;
        bin_str += bin_digit;

        frac_part -= static_cast<double>(dec_digit);

        /* don't let the output string exceed 64 characters */
        if (bin_str.size() == 64)
        {
            break;
        }
    }

    return bin_str;
}

/**
 * @brief Computes the decimal value of a number represented as a binary string.
 * @note Complexity: O(n) in time, O(1) in space, where n is the string length.
 */
double to_decimal_number(const std::string& bin_str)
{
    double number = 0.0;

    /* get the position i of bin_str where the integer part ends */
    size_t i = 0;
    while (bin_str[i] != '.' && i < bin_str.size())
    {
        ++i;
    }

    /* compute the integer part of the number  */
    double factor = 1.0;
    for (size_t j = 0; j < i; ++j)
    {
        if (bin_str[i - j - 1] == '1')
        {
            number += factor;
        }
        factor *= 2.0;
    }

    /* compute the fractional part of the number */
    factor = 0.5;
    for (size_t j = i + 1; j < bin_str.size(); ++j)
    {
        if (bin_str[j] == '1')
        {
            number += factor;
        }
        factor /= 2.0;
    }

    return number;
}

/**
 * @brief Generates a random decimal string with n digits (as an example, if
 *        n = 3 and if d represents a digit in [0,9], the output string will
 *        have one of these formats: "ddd.", "dd.d", "d.dd" or ".ddd").
 * @note Complexity: O(n) in both time and space.
 */
std::string random_decimal_string(const size_t n)
{
    /* a number with zero digits is just an empty string */
    if (n == 0)
    {
        return {};
    }

    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<size_t> dot_chooser(0, n);
    std::uniform_int_distribution<char> digit_chooser('0', '9');

    std::string dec_str;
    dec_str.reserve(n + 1);

    size_t dot_position = dot_chooser(generator);

    for (size_t k = 0; k <= n; ++k)
    {
        if (k != dot_position)
        {
            dec_str.push_back(digit_chooser(generator));
        }
        else
        {
            dec_str.push_back('.');
        }
    }

    return dec_str;
}

int main()
{
    for (size_t n = 0; n <= 10; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::string orig_dec_str = random_decimal_string(n);
            double orig_dec_num = std::atof(orig_dec_str.c_str());

            std::string comp_bin_str = to_binary_string(orig_dec_str);
            double comp_dec_num = to_decimal_number(comp_bin_str);

            assert(std::abs(orig_dec_num - comp_dec_num) < 1.e-10);
        }

        std::cout << "passed random tests for numbers with " << n << " digits"
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
