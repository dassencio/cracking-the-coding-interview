/*
 * TASK: Implement a set of stacks such that when the most recently created
 *       stack gets too high (say, with n elements), a new stack is created to
 *       accommodate new elements. When popping an element from this set of
 *       stacks, the element must be popped from the most recently created
 *       stack. Try also to create a method which can pop from any stack, in
 *       which case an element from the next stack must be moved to the replace
 *       the popped one and so on (all stacks up to the most recent one must
 *       remain full).
 */

#include "stacks.hpp"
#include <iostream>

/**
 * @brief returns the number of stacks necessary to store n elements if each
 *        stack can store at most capacity elements
 */
size_t needed_stacks(const size_t capacity, const size_t n)
{
	return (n / capacity) + (n % capacity > 0);
}

int main()
{
	for (size_t n = 0; n <= 100; ++n)
	{
		for (size_t capacity = 1; capacity <= 10; ++capacity)
		{
			stacks< int > S(capacity);
			std::vector< int > V;

			/* add elements to the stacks */
			for (size_t i = 0; i < n; ++i)
			{
				assert(S.size() == i);

				S.push(i);
				V.push_back(i);

				assert(S.top() == V.back());
			}

			/* pop all elements from the stacks */
			for (size_t i = 0; i < n; ++i)
			{
				assert(S.size() == n-i);
				assert(S.top() == V.back());

				assert(S.num_stacks() == needed_stacks(capacity, n-i));

				/* stack from which an element will be popped */
				size_t k = S.size() % S.num_stacks();

				/* if we will pop from the last stack */
				if (k+1 == S.num_stacks())
				{
					V.pop_back();
				}
				else
				{
					V.erase(V.begin() + (k+1)*capacity - 1);
				}

				S.pop_at(k);
			}

			/* the stacks should be empty */
			assert(S.size() == 0);
			assert(S.empty() == true);
			assert(S.num_stacks() == 0);

			assert(V.empty() == true);
		}

		std::cout << "passed tests for stacks of total size " << n << std::endl;
	}

	return 0;
}
