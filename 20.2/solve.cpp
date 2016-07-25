/*
 * TASK: Given a deck of cards (with 52 cards in total), shuffle them in such a
 *       way that any of the 52! possible permutations of the 52 cards is
 *       equally probable. You may assume you are given a "perfect" random
 *       number generator.
 */

#include <iostream>
#include <random>
#include <cassert>

/**
 * @brief shuffles a deck of n cards (shuffles an array with n integers)
 * @note complexity: O(n) in time, O(1) in space
 */
std::vector< size_t > shuffle_deck(std::vector< size_t >& deck)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	size_t n = deck.size();

	/*
	 * for each i in [0,n), randomly select a card among [i,n) and place it
	 * at slot i (this shuffles the deck "one card at a time")
	 */
	for (size_t i = 0; i < n; ++i)
	{
		std::uniform_int_distribution< size_t > distribution(i,n-1);

		size_t j = distribution(generator);
		std::swap(deck[i], deck[j]);
	}

	return deck;
}

/**
 * @brief returns true if a deck of n cards cards is valid, false otherwise
 * @note complexity: O(n) in both time and space
 */
bool is_valid_deck(const std::vector< size_t >& deck)
{
	std::vector< bool > cards_seen(deck.size(), false);

	for (size_t i = 0; i < deck.size(); ++i)
	{
		if (cards_seen[i] == true)
		{
			return false;
		}

		cards_seen[i] = true;
	}

	return true;
}

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::vector< size_t > deck;

			/* the deck is initially sorted */
			for (size_t i = 0; i < n; ++i)
			{
				deck.push_back(i);
			}

			shuffle_deck(deck);
			assert(is_valid_deck(deck) == true);
		}

		std::cout << "passed random tests for decks of size " << n << std::endl;
	}

	return 0;
}
