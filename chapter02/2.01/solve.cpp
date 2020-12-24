/*
 * TASK: Remove all duplicate elements from an unsorted linked list. Try solving
 *       this problem without using any additional data structures (i.e.,
 *       without generating a copy of the linked list).
 */

#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include "list.hpp"

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    for (int n = 0; n < 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::uniform_int_distribution<int> distribution(0, n);

            list<int> L1;
            list<int> L2;

            /* set of inserted values */
            std::set<int> S;

            /* L1 and L2 are copies of each other */
            for (int k = 0; k < n; ++k)
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

        std::cout << "passed random tests for lists of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
