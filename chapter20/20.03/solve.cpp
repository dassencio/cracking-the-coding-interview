/*
 * TASK: Given an array with n integers, randomly select m of them. Each
 *       combination of m from the n integers must have the same chance of
 *       being chosen.
 */

#include <iostream>
#include <random>
#include <cassert>

/**
 * @brief randomly select m elements from a vector with n >= m elements
 * @note complexity: O(n) in both time and space (but can be O(1) in space if
 *       the input vector can be modified)
 */
std::vector< size_t > random_subset(std::vector< size_t > v, const size_t m)
{
	assert(m <= v.size());

	static std::random_device device;
	static std::mt19937 generator(device());

	size_t n = v.size();

	for (size_t i = 0; i < m; ++i)
	{
		std::uniform_int_distribution< size_t > distribution(i,n-1);

		size_t j = distribution(generator);
		std::swap(v[i], v[j]);
	}

	return {v.begin(), v.begin()+m};
}

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		for (size_t m = 0; m <= n; ++m)
		{
			std::vector< size_t > values;

			for (size_t j = 0; j < n; ++j)
			{
				values.push_back(j);
			}

			for (int i = 0; i < 100; ++i)
			{
				std::vector< size_t > subset = random_subset(values,m);

				assert(subset.size() == m);

				std::vector< bool > values_seen(n, false);

				/* make sure all values are valid and don't repeat */
				for (const size_t x : subset)
				{
					assert(x < n);
					assert(values_seen[x] == false);
					values_seen[x] = true;
				}
			}
		}

		std::cout << "passed random tests for arrays of size " << n << std::endl;
	}

	return EXIT_SUCCESS;
}
