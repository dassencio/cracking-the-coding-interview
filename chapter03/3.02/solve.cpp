/*
 * TASK: Design a stack which has push and pop operations with O(1) complexity
 *       in time and space such that its minimum value can also be determined
 *       in O(1) complexity in both time and space.
 */

#include <iostream>
#include <queue>
#include <random>
#include "stack_min.hpp"

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    for (int n = 0; n <= 100; ++n)
    {
        std::uniform_int_distribution<int> distribution(-n, n);

        for (int i = 0; i < 1000; ++i)
        {
            stack_min<int> S;

            /* min-heap containing the minima of S */
            std::priority_queue<int, std::vector<int>, std::greater<int> > Q;

            /* populate the stack */
            for (int k = 0; k < n; ++k)
            {
                int value = distribution(generator);

                S.push(value);

                if (Q.empty() == true || value <= Q.top())
                {
                    Q.push(value);
                }

                assert(S.min() == Q.top());
            }

            /* pop all elements of the stack (one by one) */
            while (S.empty() == false)
            {
                assert(S.min() == Q.top());

                /* if we are removing the stack minimum node */
                if (S.top() == Q.top())
                {
                    Q.pop();
                }

                S.pop();
            }
        }

        std::cout << "passed random tests for stacks of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
