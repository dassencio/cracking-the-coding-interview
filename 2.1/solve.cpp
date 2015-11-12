#include "list.hpp"
#include <iostream>
#include <set>
#include <random>	/* std::uniform_int_distribution */
#include <cassert>

int main()
{
	std::random_device device;
	std::mt19937 generator(device());

	for (size_t n = 0; n < 100; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::uniform_int_distribution< int > distribution(0,n);

			list< int > L1;
			list< int > L2;

			/* set of inserted values */
			std::set< int > S;

			/* L1 and L2 are copies of each other */
			for (size_t i = 0; i < n; ++i)
			{
				int value = distribution(generator);

				L1.insert(value);
				L2.insert(value);
				S.insert(value);
			}

			assert(L1.size() == L2.size());

			size_t removed_1 = L1.remove_duplicates_1();
			size_t removed_2 = L2.remove_duplicates_2();

			assert(removed_1 == removed_2);

			assert(L1.size() == S.size());
			assert(L2.size() == S.size());

			for (const int value : S)
			{
				assert(L1.count(value) == 1);
				assert(L2.count(value) == 1);
			}

			/* duplicates were already removed */
			assert(L1.remove_duplicates_1() == 0);
			assert(L2.remove_duplicates_2() == 0);
		}

		std::cout << "passed random tests for lists of length " << n << std::endl;
	}

	return 0;
}
