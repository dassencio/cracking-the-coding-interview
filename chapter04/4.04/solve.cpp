/*
 * TASK: For a given binary search tree, build a list whose k-th element is a
 *       list of all nodes at the k-th tree level. The first list element must
 *       be a list with only the root node, the second list should be a list
 *       containing only the children of the root node and so on.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include "binary_search_tree.hpp"

/**
 * @brief Generates a random vector of length n and values in [0,n].
 * @note Complexity: O(n) in both time and space.
 */
std::vector<size_t> random_vector(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<size_t> distribution(0, n);

    std::vector<size_t> values;

    while (values.size() < n)
    {
        values.push_back(distribution(generator));
    }

    return values;
}

int main()
{
    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            binary_search_tree<size_t> tree;

            std::vector<size_t> keys = random_vector(n);

            for (const size_t x : keys)
            {
                tree.insert(x);
            }

            assert(tree.size() == n);

            /*
             * get the lists of nodes at each level using both BFS and
             * DFS, then compare the results from both methods
             */
            std::vector<std::list<size_t> > lists_bfs =
                tree.level_node_list_bfs();
            std::vector<std::list<size_t> > lists_dfs =
                tree.level_node_list_dfs();

            assert(lists_bfs == lists_dfs);
            assert(tree.height() == lists_bfs.size());

            /*
             * put all keys obtained at each level into a single
             * (flattened) vector, then make sure this vector contains
             * exactly the keys inserted in the tree
             */
            std::vector<size_t> bfs_keys;

            for (const std::list<size_t>& level_keys : lists_bfs)
            {
                bfs_keys.insert(
                    bfs_keys.end(), level_keys.begin(), level_keys.end());
            }

            std::sort(keys.begin(), keys.end());
            std::sort(bfs_keys.begin(), bfs_keys.end());

            assert(bfs_keys == keys);
        }

        std::cout << "passed tests for trees of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
