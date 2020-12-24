/*
 * TASK: Create an algorithm which sorts a stack in ascending order (i.e., the
 *       stack top will be its minimum element after sorting). Only use the
 *       push, pop, top and is_empty operations of your stack implementation.
 */

#include <cassert>
#include <iostream>
#include <random>
#include <stack>

/**
 * @brief Sorts a stack A with n elements in ascending order (i.e., the stack
 *        top will be its minimum element after sorting).
 * @note Complexity: O(n²) in time, O(n) in space.
 */
template<typename T>
void sort_stack(std::stack<T>& A)
{
    std::stack<T> B;

    while (A.empty() == false)
    {
        /* take A's top element, call it a */
        T a = A.top();
        A.pop();

        /*
         * as long as B's top element is smaller than a, put B's top
         * element back on top of A
         */
        while (B.empty() == false && B.top() < a)
        {
            A.push(B.top());
            B.pop();
        }

        /*
         * at this point, B is either empty or has a top element
         * which is larger than or equal to a, so put a on B
         */
        B.push(a);
    }

    A = B;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    for (size_t n = 0; n <= 50; ++n)
    {
        std::uniform_int_distribution<size_t> distribution(0, n);

        for (int i = 0; i < 1000; ++i)
        {
            std::stack<size_t> A;

            /* add elements to the stack */
            while (A.size() < n)
            {
                A.push(distribution(generator));
            }

            sort_stack(A);

            assert(A.size() == n);

            size_t a = 0;

            /* check if the stack is now sorted */
            while (A.empty() == false)
            {
                assert(A.top() >= a);
                a = A.top();
                A.pop();
            }
        }

        std::cout << "passed random tests for stacks of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
