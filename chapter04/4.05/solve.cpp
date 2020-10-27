/*
 * TASK: Given a binary search tree and one of its nodes, determine the in-order
 *       successor of this node.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

/** @brief A node of a binary search tree. */
struct tree_node
{
    size_t key;
    tree_node* left;
    tree_node* right;
    tree_node* parent;

    ~tree_node()
    {
        delete left;
        delete right;
    }
};

/**
 * @brief Returns a pointer to a node in a binary search containing a given key
 *        or nullptr is no such node exists.
 * @param root The root node of the tree.
 * @param key The key to search for.
 * @note Complexity: O(n) in both time and space, where n is the number of tree
 *       nodes.
 */
const tree_node* find(const tree_node* root, const size_t key)
{
    if (root == nullptr || key == root->key)
    {
        return root;
    }

    return (key < root->key) ? find(root->left, key) : find(root->right, key);
}

/**
 * @brief Inserts a node with a given key into a binary search tree.
 * @param root The root node of the tree.
 * @param key The key to be inserted.
 * @note Complexity: O(n) in both time and space, where n is the number of tree
 *       nodes.
 */
void insert(tree_node* root, const size_t key)
{
    if (key < root->key)
    {
        if (root->left == nullptr)
        {
            root->left = new tree_node{key, nullptr, nullptr, root};
        }
        else
        {
            insert(root->left, key);
        }
    }
    else if (key > root->key)
    {
        if (root->right == nullptr)
        {
            root->right = new tree_node{key, nullptr, nullptr, root};
        }
        else
        {
            insert(root->right, key);
        }
    }
}

/**
 * @brief Returns a pointer to the in-order successor of a given node.
 * @note Complexity: O(n) in time, O(1) in space, where n is the number of tree
 *       nodes.
 */
const tree_node* successor(const tree_node* node)
{
    /*
     * if node has a right subtree, its successor is the leftmost node
     * of that subtree; if node has no right subtree, its successor can
     * only be one of its ancestors
     */
    if (node->right != nullptr)
    {
        const tree_node* current = node->right;

        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }
    else
    {
        const tree_node* current = node->parent;

        while (current != nullptr && current->key < node->key)
        {
            current = current->parent;
        }

        return current;
    }

    return nullptr;
}

/**
 * @brief Generates a random binary search tree with n nodes and returns a
 *        pointer to its root node (the node keys are 0, 1, ..., n-1).
 * @note Complexity: O(n²) in time, O(n) in space.
 */
const tree_node* random_binary_search_tree(const size_t n)
{
    if (n == 0)
    {
        return nullptr;
    }

    std::vector<size_t> keys;

    for (size_t i = 0; i < n; ++i)
    {
        keys.push_back(i);
    }

    static std::random_device device;
    static std::mt19937 generator(device());

    std::shuffle(keys.begin(), keys.end(), generator);

    /* start with the root node */
    tree_node* root = new tree_node{keys[0], nullptr, nullptr, nullptr};

    for (size_t i = 1; i < n; ++i)
    {
        insert(root, keys[i]);
    }

    return root;
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            const tree_node* root = random_binary_search_tree(n);

            for (size_t key = 0; key < n; ++key)
            {
                const tree_node* node = find(root, key);
                assert(node != nullptr && node->key == key);

                if (key == n - 1)
                {
                    assert(successor(node) == nullptr);
                }
                else
                {
                    assert(successor(node)->key == key + 1);
                }
            }

            delete root;
        }

        std::cout << "passed random tests for trees of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
