#include <iostream>
#include <cstring>	/* std::strlen */
#include <algorithm>	/* std::reverse */
#include <cassert>

/**
 * @brief reverses an input C-string in place
 * @return pointer to input string (reversed)
 * @note complexity: O(n) in time, O(1) in space, where n is the string length
 */
char* reverse_c_string(char* str)
{
	size_t len = std::strlen(str);

	if (len <= 1)
	{
		return str;
	}

	char* first = str;
	char* last = str + len - 1;

	while (first < last)
	{
		std::swap(*first, *last);
		first++;
		last--;
	}

	return str;
}

/**
 * @brief generates a random C-string of length n and characters in [a-z]
 * @note complexity: O(n) in both space and time
 */
char* random_string(size_t n)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution< int > distribution(0,25);

	char* str = new char[n+1];
	str[n] = '\0';

	while (n > 0)
	{
		--n;
		str[n] = 'a' + distribution(generator);
	}

	return str;
}

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			char* str = random_string(n);
			std::string str_copy(str);

			reverse_c_string(str);
			std::reverse(str_copy.begin(), str_copy.end());

			assert(strcmp(str, str_copy.c_str()) == 0);

			delete[] str;
		}

		std::cout << "passed random tests for strings of length " << n << std::endl;
	}

	return 0;
}
