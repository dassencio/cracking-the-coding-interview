/*
 * NOTE: the question is asking you to determine if a string has duplicate
 *       characters or not
 */

#include <iostream>
#include <string>
#include <algorithm>	/* std::sort */
#include <cassert>

/**
 * @brief solution using a bitmask to mark the seen characters
 * @note complexity: O(n) in time, O(1) in space
 * @note this implementation assumes all characters are in the range [a-z]
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
 * @brief solution without using any additional data structures
 * @note complexity: O(n*log(n)) in time, O(n) in space (but can be O(1) in
 *       space if we don't mind losing the original string str since we can
 *       sort it in place instead of sorting a copy of it)
 */
bool has_duplicates_2(std::string str)
{
	std::sort(str.begin(), str.end());

	/* detect duplicate characters */
	for (size_t i = 0; i+1 < str.size(); ++i)
	{
		if (str[i] == str[i+1])
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief brute-force solution: check all characters against each other
 * @note complexity: O(n²) in time, O(1) in space
 */
bool has_duplicates_3(const std::string& str)
{
	 for (size_t i = 0; i < str.size(); ++i)
	 {
		 for (size_t j = i+1; j < str.size(); ++j)
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
 * @brief generates a random string of length n and characters in [a-z]
 * @note complexity: O(n) in both space and time
 */
std::string random_string(size_t n)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution< int > distribution(0,25);

	std::string str;

	while (n > 0)
	{
		char letter = 'a' + distribution(generator);
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

			bool result = has_duplicates_3(str);

			assert(has_duplicates_1(str) == result);
			assert(has_duplicates_2(str) == result);
		}

		std::cout << "passed random tests for strings of length " << n << std::endl;
	}

	return 0;
}
