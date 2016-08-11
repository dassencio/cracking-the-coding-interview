/*
 * TASK: You are given an n×n square board such that each cell is either black
 *       or white. Determine the largest (in area) subsquare of the board such
 *       that all cells at its borders are black.
 */

#include <vector>
#include <iostream>
#include <random>
#include <cassert>

/*
 * @brief generic board class for storing data per cell
 */
template< typename T >
class board
{
public:
	board(const size_t n): element(n, std::vector< T >(n))
	{
		/* nothing here */
	}

	T& operator()(const size_t i, const size_t j)
	{
		assert(i < size() && j < size());
		return element[i][j];
	}

	const T& operator()(const size_t i, const size_t j) const
	{
		assert(i < size() && j < size());
		return element[i][j];
	}

	size_t size() const
	{
		return element.size();
	}

private:
	std::vector< std::vector< T > > element;
};

/**
 * @brief square class which defines a square by the position of its bottom left
 *        corner cell as well as the edge length in number of cells
 */
struct square
{
	size_t area() const
	{
		return L*L;
	}

	size_t x;
	size_t y;
	size_t L;
};

enum class color { WHITE, BLACK };

/**
 * @brief returns true if the square S has black borders, false otherwise
 * @note complexity: O(1) in space, O(n) in time, where n is the board size
 */
bool is_valid_solution(const square& S, const board< color >& B)
{
	const size_t L = S.L;
	const size_t x = S.x;
	const size_t y = S.y;

	/* check if the top and bottom borders are black */
	for (size_t i = x; i < x+L; ++i)
	{
		if (B(i,y) == color::WHITE || B(i,y+L-1) == color::WHITE)
		{
			return false;
		}
	}

	/* check if the left and right borders are black */
	for (size_t j = y; j < y+L; ++j)
	{
		if (B(x,j) == color::WHITE || B(x+L-1,j) == color::WHITE)
		{
			return false;
		}
	}

	return true;
}

/**
 * @brief returns the largest square with black borders
 * @note complexity: O(n²) in space, O(n³) in time, where n is the board size
 */
square maximum_subsquare_1(const board< color >& B)
{
	size_t n = B.size();

	/* number of black cells to the left including self */
	board< size_t > black_left(n);

	/* number of black cells below including self */
	board< size_t > black_down(n);

	square result{0,0,0};

	/*
	 * for each black cell, compute the number of black cells below and to
	 * its left (including the cell itself), the total work is O(n²) in time
	 */
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			black_left(i,j) = (B(i,j) == color::BLACK);
			black_down(i,j) = (B(i,j) == color::BLACK);

			if (i > 0 && B(i,j) == color::BLACK)
			{
				black_left(i,j) += black_left(i-1,j);
			}
			if (j > 0 && B(i,j) == color::BLACK)
			{
				black_down(i,j) += black_down(i,j-1);
			}
		}
	}

	/*
	 * now find the largest square with black borders; the total work is
	 * O(n³) in time
	 */
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			/*
			 * max_L is the maximum possible length of a square
			 * with black borders and bottom left position (i,j)
			 */
			size_t max_L = std::min(n-i, n-j);

			for (size_t L = max_L; L*L > result.area(); --L)
			{
				/*
				 * check if the square with bottom left position
				 * (i,j) and length L has black borders
				 */
				if (black_left(i+L-1,j) >= L &&
				    black_down(i+L-1, j+L-1) >= L &&
				    black_left(i+L-1, j+L-1) >= L &&
				    black_down(i, j+L-1) >= L)
				{
					result.x = i;
					result.y = j;
					result.L = L;
				}
			}
		}
	}

	return result;
}

/**
 * @brief returns the largest square with black borders using brute force
 * @note complexity: O(1) in space, O(n^4) in time, where n is the board size
 */
square maximum_subsquare_2(const board< color >& B)
{
	size_t n = B.size();

	square result{0,0,0};

	/*
	 * for every position (i,j), determine the largest square which has
	 * (i,j) as its bottom left cell and black borders
	 */
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			/*
			 * max_L is the maximum possible length of a square
			 * with black borders and bottom left position (i,j)
			 */
			size_t max_L = std::min(n-i, n-j);

			for (size_t L = max_L; L*L > result.area(); --L)
			{
				square S{i,j,L};

				/* check in O(n) time if S has black borders */
				if (is_valid_solution(S,B) == true)
				{
					result = S;
				}
			}
		}
	}

	return result;
}

/**
 * @brief generates a random n×n board with black and white cells, where cells
 *        are black with probability 80% and white with probability 20%
 * @note complexity: O(n²) in both time and space
 */
board< color > random_board(const size_t n)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	std::bernoulli_distribution distribution(0.8);

	board< color > B(n);

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			B(i,j) = distribution(generator) == true ? color::BLACK : color::WHITE;
		}
	}

	return B;
}

int main()
{
	for (size_t n = 0; n <= 20; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			board< color > B = random_board(n);

			square S1 = maximum_subsquare_1(B);
			square S2 = maximum_subsquare_2(B);

			assert(is_valid_solution(S1,B) == true);
			assert(is_valid_solution(S2,B) == true);

			assert(S1.area() == S2.area());
		}

		std::cout << "passed random tests for boards of size " << n << std::endl;
	}

	return 0;
}
