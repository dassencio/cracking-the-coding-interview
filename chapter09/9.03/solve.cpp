/*
 * TASK: Implement the binary search algorithm for an initially sorted array
 *       which has been rotated, i.e., whose elements have been periodically
 *       shifted to the right by an unknown offset k. The complexity of your
 *       algorithm should be O(log(n)) in time, O(1) in space. As an example,
 *       given an array { 8 9 10 1 2 3 4 5 6 7 } (i.e., an array initially
 *       containing all integers in [1,9] which has been rotated three elements
 *       to the right), searching for the value 1 returns 3, searching for the
 *       value 10 returns 2 and searching for the value 5 returns 7.
 *
 * NOTE: The solution presented here assumes all array values are unique (the
 *       problem is not solved as stated if duplicate values are allowed).
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

/**
 * @brief Returns the position of a value x in a sorted-then-rotated array v or
 *        the size of v is x is not in v.
 * @note Complexity: O(log(n)) in time, O(1) in space.
 * @note The algorithm is based on the fact that the rotated array has two
 *       sections: the elements on the left section are strictly larger than
 *       the elements on the right section, and each section is internally
 *       sorted in ascending order (e.g. in { 8 9 10 1 2 3 4 5 6 7 }, the left
 *       section is { 8 9 10 } and the right section is { 1 2 3 4 5 6 7 }).
 */
size_t binary_search(const std::vector< int >& v, const int x)
{
	if (v.empty() == true)
	{
		return 0;
	}

	size_t left = 0;
	size_t right = v.size()-1;

	while (left != right)
	{
		/* middle < right (always) */
		size_t middle = left + (right-left)/2;

		/* if middle is at the left section of v */
		if (v[left] <= v[middle])
		{
			/* if x is to the right of middle */
			if (v[middle] < x || x < v[left])
			{
				left = middle + 1;
			}
			else
			{
				right = middle;
			}
		}
		/* if middle is at the right section of v */
		else
		{
			/* if x is either at middle or to its left */
			if (v[left] <= x || x <= v[middle])
			{
				right = middle;
			}
			else
			{
				left = middle + 1;
			}
		}
	}

	return (v[left] == x) ? left : v.size();
}

int main()
{
	for (int n = 0; n <= 100; ++n)
	{
		std::vector< int > v(n);

		for (int i = 0; i < n; ++i)
		{
			v[i] = i;
		}

		/* try all possible rotations for v */
		for (int i = 0; i < n; ++i)
		{
			std::rotate(v.begin(), std::next(v.begin(),i), v.end());

			/* search for each value x in [-n,2n] in v */
			for (int x = -n; x <= 2*n; ++x)
			{
				if (0 <= x && x < n)
				{
					assert(v[binary_search(v,x)] == x);
				}
				else
				{
					assert(binary_search(v,x) == v.size());
				}
			}
		}

		std::cout << "passed tests for arrays of size " << n << std::endl;
	}

	return EXIT_SUCCESS;
}
