/*
 * TASK: Given a large text file and two words, determine the shortest distance
 *       between any two occurrences of such words in number of words.
 */

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cassert>

const size_t infinity = std::numeric_limits< size_t >::max();

/**
 * @brief Computes the shortest distance between two words in an array of n
 *        words.
 * @note Complexity: O(n*k) in time, O(1) in space, where k is the length of
 *       the shortest string among word1 and word2.
 */
size_t shortest_distance_1(const std::vector< std::string >& words,
                           const std::string& word1,
                           const std::string& word2)
{
	size_t closest = infinity;

	/* last occurrences of word1 and word2 respectively */
	size_t last_occurrence[2] = { infinity, infinity };

	for (size_t i = 0; i < words.size(); ++i)
	{
		if (words[i] == word1)
		{
			last_occurrence[0] = i;

			/* if we have already found an occurrence of word2 */
			if (last_occurrence[1] != infinity)
			{
				closest = std::min(closest, i - last_occurrence[1]);
			}
		}
		if (words[i] == word2)
		{
			last_occurrence[1] = i;

			/* if we have already found an occurrence of word1 */
			if (last_occurrence[0] != infinity)
			{
				closest = std::min(closest, i - last_occurrence[0]);
			}
		}
	}

	return closest;
}

/**
 * @brief Computes the shortest distance between two words in an array of n
 *        words.
 * @note Complexity: O(n*k) in time, O(n) in space, where k is the length of
 *       the shortest string among word1 and word2.
 */
size_t shortest_distance_2(const std::vector< std::string >& words,
                           const std::string& word1,
                           const std::string& word2)
{
	struct entry
	{
		size_t index;
		size_t word;  /* 0 for word1, 1 for word2 */
	};

	std::vector< entry > occurrences;

	/* scan the words array for all occurrences of word1 and word2 */
	for (size_t i = 0; i < words.size(); ++i)
	{
		if (words[i] == word1)
		{
			occurrences.push_back(entry{i,0});
		}
		if (words[i] == word2)
		{
			occurrences.push_back(entry{i,1});
		}
	}

	size_t closest = infinity;

	for (size_t i = 0; i+1 < occurrences.size(); ++i)
	{
		const entry& e1 = occurrences[i];
		const entry& e2 = occurrences[i+1];

		if (e1.word != e2.word)
		{
			closest = std::min(closest, e2.index - e1.index);
		}
	}

	return closest;
}

/**
 * @brief Generates a random ASCII string of random length in [1,10] with
 *        characters in [a-d].
 * @note Complexity: O(1) in both time and space.
 */
std::string random_string()
{
	static std::random_device device;
	static std::mt19937 generator(device());

	std::uniform_int_distribution< size_t > size_chooser(1,10);
	std::uniform_int_distribution< char > letter_chooser('a','d');

	size_t size = size_chooser(generator);

	std::string str;

	while (str.size() < size)
	{
		str.push_back(letter_chooser(generator));
	}

	return str;
}

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		/* the input file is represented as an array of words */
		std::vector< std::string > words;

		while (words.size() < n)
		{
			words.push_back(random_string());
		}

		for (const std::string& word1 : words)
		{
			for (const std::string& word2 : words)
			{
				assert(shortest_distance_1(words, word1, word2) ==
				       shortest_distance_2(words, word1, word2));
			}
		}

		/*
		 * get the distance between random string pairs (many of those
		 * pairs will contain strings which are not in the words array)
		 */
		for (int k = 0; k < 1000; ++k)
		{
			std::string word1 = random_string();
			std::string word2 = random_string();

			assert(shortest_distance_1(words, word1, word2) ==
			       shortest_distance_2(words, word1, word2));
		}

		std::cout << "passed random test for file with " << n << " words" << std::endl;
	}

	return EXIT_SUCCESS;
}
