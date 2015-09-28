#include <iostream>
#include <string>
#include <bitset>
#include <random>	/* std::random_device, std::uniform_int_distribution */
#include <cassert>

/**
 * @brief solution without using an additional buffer
 * @return reference to input string with all duplicate characters removed
 * @note complexity: O(n²) in time, O(1) in space
 */
std::string& remove_duplicates_1(std::string& str)
{
	if (str.size() <= 1)
	{
		return str;
	}

	/* next writing position (the first character is skipped) */
	size_t i = 1;

	/* invariant: str[0..i) has no duplicate characters */
	for (size_t j = 1; j < str.size(); ++j)
	{
		size_t k = 0;

		while (k < i)
		{
			/* if str[j] is a duplicate character */
			if (str[k] == str[j])
			{
				break;
			}
			++k;
		}

		/* if str[j] is a character not seen so far */
		if (k == i)
		{
			str[i] = str[j];
			++i;
		}
	}

	/* all characters in str[i..str.size()) are duplicates, discard them */
	str.resize(i);

	return str;
}

/**
 * @brief solution using a fixed-size array to track seen characters (the input
 *        string is assumed to contain only valid ASCII characters)
 * @return reference to input string with all duplicate characters removed
 * @note complexity: O(n) in time, O(1) in space
 */
std::string& remove_duplicates_2(std::string& str)
{
	if (str.size() <= 1)
	{
		return str;
	}

	std::bitset< 128 > seen{};

	/* next writing position (the first character is skipped) */
	size_t i = 1;

	/* the first character is seen and skipped */
	seen[str[0]] = true;

	for (size_t j = 1; j < str.size(); ++j)
	{
		if (seen[str[j]] == false)
		{
			seen[str[j]] = true;

			str[i] = str[j];
			++i;
		}
	}

	/* all characters in str[i..str.size()) are duplicates, discard them */
	str.resize(i);

	return str;
}

/**
 * @brief generates a random string of length n
 * @note complexity: O(n) in both space and time
 */
std::string random_string(size_t n)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution< int > distribution(0,127);

	std::string str;

	while (n > 0)
	{
		char letter = distribution(generator);
		str.push_back(letter);
		--n;
	}

	return str;
}

int main()
{
	for (int n = 0; n <= 100; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::string str = random_string(n);
			std::string str_copy(str);

			remove_duplicates_1(str);
			remove_duplicates_2(str_copy);

			assert(str == str_copy);
		}

		std::cout << "passed random tests for strings of length " << n << std::endl;
	}

	return 0;
}
