/*
 * TASK: Construct a binary tree with minimal height from the values of a
 *       sorted array.
 *
 * NOTE: The tree constructed by the algorithm below is balanced but is not
 *       always a binary search tree (e.g. when all values in the tree are
 *       equal); it is, however, "ordered" in the sense that for a given node,
 *       all keys on its left subtree are smaller than or equal to this node's
 *       key and all keys on its right subtree are larger than or equal to this
 *       node's key.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/** @brief A node of a binary tree. */
struct tree_node
{
    int key;

    tree_node* left = nullptr;
    tree_node* right = nullptr;

    ~tree_node()
    {
        delete left;
        delete right;
    }
};

/**
 * @brief Builds a tree with minimum height with the values in a sorted array.
 * @param begin A bidirectional iterator pointing to the first array element.
 * @param end A bidirectional iterator pointing to one past the last array
 *        element.
 * @return A pointer to the tree's root node.
 * @note Complexity: O(n) in time, O(log(n)) in space, where n is the number of
 *       elements in the array, because the recursion will not go deeper than
 *       O(log(n)) levels.
 */
template<typename bidirectional_iterator>
tree_node* build_min_height_tree(const bidirectional_iterator begin,
                                 const bidirectional_iterator end)
{
    if (begin == end)
    {
        return nullptr;
    }

    const bidirectional_iterator middle = begin + std::distance(begin, end) / 2;

    tree_node* node = new tree_node;

    node->key = *middle;
    node->left = build_min_height_tree(begin, middle);
    node->right = build_min_height_tree(middle + 1, end);

    return node;
}

/**
 * @brief Returns the length of the longest root-to-leaf path in a binary tree.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in time, O(k) in space, where n is the number of tree
 *       nodes and k is the tree height, because the recursion will not go
 *       deeper than k levels.
 */
size_t tree_height(const tree_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + std::max(tree_height(root->left), tree_height(root->right));
}

/**
 * @brief Returns true if the tree is "ordered", false otherwise, where
 *        "ordered" is defined as in the note on top of this file.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in time, O(k) in space, where n is the number of tree
 *       nodes and k is the tree height, because the recursion will not go
 *       deeper than k levels.
 */
bool is_ordered_tree(const tree_node* root,
                     const int min_allowed = std::numeric_limits<int>::min(),
                     const int max_allowed = std::numeric_limits<int>::max())
{
    if (root == nullptr)
    {
        return true;
    }

    /* root->key must be within [min_allowed, max_allowed] */
    if (root->key < min_allowed || root->key > max_allowed)
    {
        return false;
    }

    return is_ordered_tree(root->left, min_allowed, root->key) &&
           is_ordered_tree(root->right, root->key, max_allowed);
}

/**
 * @brief Returns the number of occurrences of a value in a binary tree.
 * @param root The root node of the tree.
 * @param x The value to search for.
 * @note Complexity: O(n) in time, O(k) in space, where n is the number of tree
 *       nodes and k is the tree height, because the recursion will not go
 *       deeper than k levels.
 */
size_t count(const tree_node* root, const int x)
{
    if (root == nullptr)
    {
        return 0;
    }

    return (root->key == x) + count(root->left, x) + count(root->right, x);
}

/**
 * @brief Generates a sorted random vector of length n and values in [-n,n].
 * @note Complexity: O(n*log(n)) in time, O(n) in space.
 */
std::vector<int> sorted_random_vector(int n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-n, n);

    std::vector<int> values;

    while (n > 0)
    {
        values.push_back(distribution(generator));
        --n;
    }

    std::sort(values.begin(), values.end());

    return values;
}

int main()
{
    for (int n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<int> values = sorted_random_vector(n);

            tree_node* root =
                build_min_height_tree(values.begin(), values.end());

            /*
             * a minimum-height tree has height floor(log2(n))+1, where n is the
             * number of elements in the tree; the only exception happens for an
             * empty tree, in which case its height is zero
             */
            if (n == 0)
            {
                assert(tree_height(root) == 0);
            }
            else
            {
                assert(tree_height(root) ==
                       static_cast<size_t>(std::log2(n)) + 1);
            }

            assert(is_ordered_tree(root));

            for (const int x : values)
            {
                size_t occurrences =
                    std::count(values.begin(), values.end(), x);
                assert(count(root, x) == occurrences);
            }

            delete root;
        }

        std::cout << "passed random tests for trees of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
