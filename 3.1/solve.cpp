#include "three_stacks.hpp"
#include <iostream>

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		/* three stacks, each with maximum size n */
		three_stacks< size_t > S(n);

		/* all stacks should be empty at this point */
		for (size_t k = 0; k <= 2; ++k)
		{
			assert(S.empty(k) == true);
		}

		/* insert n elements on each stack */
		for (size_t k = 0; k <= 2; ++k)
		{
			for (size_t i = 0; i < n; ++i)
			{
				assert(S.size(k) == i);
				assert(S.push(k, k*n + i) == true);
			}
		}

		/* all stacks should be full now, so new insertions must fail */
		for (size_t k = 0; k <= 2; ++k)
		{
			assert(S.size(k) == n);
			assert(S.push(k,0) == false);
		}

		/* pop all elements of each stack */
		for (size_t k = 0; k <= 2; ++k)
		{
			for (size_t i = 0; i < n; ++i)
			{
				assert(S.size(k) == n-i);
				assert(S.top(k) == k*n + (n-i-1));
				S.pop(k);
			}

			assert(S.empty(k) == true);
		}

		/* trying to pop further should have no effect */
		for (size_t k = 0; k <= 2; ++k)
		{
			S.pop(k);
			assert(S.empty(k) == true);
		}

		std::cout << "passed tests for stacks of size " << n << std::endl;
	}

	return 0;
}
