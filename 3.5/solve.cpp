#include "two_stacks_queue.hpp"
#include <iostream>

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		two_stacks_queue< size_t > Q;

		/* push elements onto the queue */
		for (size_t i = 0; i < n; ++i)
		{
			assert(Q.size() == i);

			Q.push(i);

			/* run tests on Q without modifying it */
			two_stacks_queue< size_t > R = Q;
			assert(R.front() == 0);
			assert(R.back() == i);
		}

		/* pop all elements from the queue */
		for (size_t i = 0; i < n; ++i)
		{
			assert(Q.size() == n-i);

			/* run tests on Q without modifying it */
			two_stacks_queue< size_t > R = Q;
			assert(R.front() == i);
			assert(R.back() == n-1);

			Q.pop();
		}

		assert(Q.empty() == true);

		std::cout << "passed tests for queues of length " << n << std::endl;
	}

	return 0;
}
