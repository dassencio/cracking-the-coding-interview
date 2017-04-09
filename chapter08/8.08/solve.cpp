/*
 * TASK: Given a chess board and eight queens, determine all possible ways in
 *       which the eight queens can be placed on the board such that no queens
 *       are in the same row, column or diagonal.
 */

#include <array>
#include <list>
#include <iostream>
#include <cassert>

/*
 * a position (i,j) represents a (row,column) position on the chess board, with
 * (0,0) being the bottom-left square
 */
using position = std::array< uint64_t,2 >;

/* a "queen setup" defines the positions of all (eight) queens */
using queen_setup = std::list< position >;

/**
 * @brief generates a unique bitmask corresponding to position (i,j) on the
 *        chess board: (i,j) --> 8*i + j
 * @note complexity: O(1) in both time and space
 */
uint64_t position_mask(const uint64_t i, const uint64_t j)
{
	assert(i < 8 && j < 8);
	return uint64_t(1) << (uint64_t(8)*i + j);
}

/**
 * @brief returns true if a queen can be placed at (i,j), false otherwise
 * @note complexity: O(1) in both time and space
 */
bool is_blocked(const uint64_t blocked, const uint64_t i, const uint64_t j)
{
	return (blocked & position_mask(i,j)) != 0;
}

/**
 * @brief returns an updated 'blocked' bitmask if a queen is placed at (i,j),
 *        i.e., a bitmask which marks the row, column and diagonals passing
 *        through (i,j) as "blocked" (no queen can be placed there) on top of
 *        its previous status
 * @note complexity: O(1) in both time and space
 */
uint64_t place_queen(uint64_t blocked, const uint64_t i, const uint64_t j)
{
	/* block the i-th row and the j-th column */
	for (uint64_t k = 0; k < 8; ++k)
	{
		/* row, column */
		blocked |= position_mask(i,k);
		blocked |= position_mask(k,j);
	}

	/* block the diagonals going over (i,j) */
	for (uint64_t k = 1; k < 8; ++k)
	{
		/* diagonal towards top and right */
		blocked |= (i+k < 8 && j+k < 8) ? position_mask(i+k, j+k) : 0;

		/* diagonal towards top and left */
		blocked |= (i+k < 8 && j >= k)  ? position_mask(i+k, j-k) : 0;

		/* diagonal towards bottom and left */
		blocked |= (i >= k && j >= k)   ? position_mask(i-k, j-k) : 0;

		/* diagonal towards bottom and right */
		blocked |= (i >= k && j+k < 8)  ? position_mask(i-k, j+k) : 0;
	}

	return blocked;
}

/**
 * @brief returns a vector with all valid solutions to the eight queens problem
 * @param blocked a bitmask representing the positions where a queen cannot be
 *        placed
 * @param j the current column where we are trying to place a queen (this index
 *        is equivalent to how many queens we have added so far to the chess
 *        board because each column must contain exactly one queen, otherwise
 *        some column would have to contain at least two queens, but this is not
 *        valid according to the rules of the game)
 * @note complexity: O(1) in both time and space
 */
std::list< queen_setup > eight_queens(const uint64_t blocked = 0, const uint64_t j = 0)
{
	/* base case: no more queens to place on the chess board */
	if (j == 8)
	{
		return { {} };
	}

	std::list< queen_setup > setups;

	/*
	 * we are on the j-th column; try placing a queen on each row i
	 * such that (i,j) is unblocked and then proceed recursively
	 */
	for (uint64_t i = 0; i < 8; ++i)
	{
		/* if we can place a queen at (i,j) */
		if (is_blocked(blocked, i, j) == false)
		{
			uint64_t new_blocked = place_queen(blocked, i, j);

			/* solve the problem recursively on columns [j+1..8) */
			std::list< queen_setup > __setups = eight_queens(new_blocked, j+1);

			/* place the queen at (i,j) for each sub-problem solution */
			for (queen_setup& setup : __setups)
			{
				setup.push_front(position{i,j});
			}

			setups.splice(setups.end(), __setups);
		}
	}

	return setups;
}

/**
 * @brief returns true if setup is a valid solution to the eight queens problem,
 *        false otherwise
 * @note complexity: O(1) in both time and space
 */
bool is_valid_solution(const queen_setup& setup)
{
	uint64_t blocked = 0;

	for (const position& p : setup)
	{
		if (is_blocked(blocked, p[0], p[1]) == true)
		{
			return false;
		}

		blocked = place_queen(blocked, p[0], p[1]);
	}

	return (setup.size() == 8);
}

int main()
{
	std::list< queen_setup > setups = eight_queens();

	for (const queen_setup& setup : setups)
	{
		for (const position& p : setup)
		{
			std::cout << "(" << p[0] << "," << p[1] << ") ";
		}
		std::cout << std::endl;

		assert(is_valid_solution(setup));
	}

	return EXIT_SUCCESS;
}
