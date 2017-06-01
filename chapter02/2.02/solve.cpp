/*
 * TASK: Given a singly-linked list, determine its n-th to last element.
 */

#include <cassert>
#include <iostream>
#include "list.hpp"

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        list<size_t> L;

        for (size_t i = 0; i < n; ++i)
        {
            L.insert(i);
        }

        assert(L.size() == n);

        for (size_t i = 0; i < n; ++i)
        {
            assert(L.get_nth_to_last(i) == i);
        }

        std::cout << "passed tests for lists of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
