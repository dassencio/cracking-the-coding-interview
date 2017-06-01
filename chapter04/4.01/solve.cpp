/*
 * TASK: Given a binary tree, determine if it is balanced. In this question,
 *       "balanced" means the smallest and largest distances between the
 *       leaf nodes and the root node cannot differ by more than one.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/* a binary tree is represented here by its root node */
struct tree_node
{
    tree_node* left = nullptr;
    tree_node* right = nullptr;

    ~tree_node()
    {
        delete left;
        delete right;
    }
};

/**
 * @brief Returns the length of the longest root-to-leaf path in a binary tree.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in both time and space because the recursion will not
 *       go deeper than n levels, where n is the total number of tree nodes.
 */
size_t longest_path_length(const tree_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + std::max(longest_path_length(root->left),
                        longest_path_length(root->right));
}

/**
 * @brief Returns the length of the shortest root-to-leaf path in a binary tree.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in both time and space because the recursion will not
 *       go deeper than n levels, where n is the total number of tree nodes.
 */

size_t shortest_path_length(const tree_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + std::min(shortest_path_length(root->left),
                        shortest_path_length(root->right));
}

/**
 * @brief Returns true if a given binary tree is balanced, false otherwise.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in both time and space, where n is the total number
 *       of tree nodes.
 */
bool is_balanced_tree(const tree_node* root)
{
    return (longest_path_length(root) - shortest_path_length(root) <= 1);
}

/**
 * @brief Returns the number of nodes in a binary tree.
 * @param root The root node of the tree.
 * @note Complexity: O(n) in both time and space because the recursion will not
 *       go deeper than n levels, where n is the total number of tree nodes.
 */
size_t num_nodes(const tree_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + num_nodes(root->left) + num_nodes(root->right);
}

/**
 * @brief Generates a balanced binary tree with n nodes.
 * @param n The number of tree nodes to generate.
 * @note Complexity: O(n²) in time, O(n) in space.
 */
tree_node* balanced_binary_tree(size_t n)
{
    if (n == 0)
    {
        return nullptr;
    }

    /* start with the root node only */
    std::vector<tree_node*> nodes = {new tree_node};
    --n;

    while (n > 0)
    {
        nodes.push_back(new tree_node);

        /* find the first node which has an empty left/right child */
        auto it =
            std::find_if(nodes.begin(), nodes.end(), [](const tree_node* node) {
                return node->left == nullptr || node->right == nullptr;
            });

        tree_node* node = *it;

        if (node->left == nullptr)
        {
            node->left = nodes.back();
        }
        else
        {
            node->right = nodes.back();
        }

        --n;
    }

    return nodes.front();
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        tree_node* root = balanced_binary_tree(n);

        assert(num_nodes(root) == n);
        assert(is_balanced_tree(root) == true);

        delete root;

        /*
         * test as well against an unbalanced tree (but keep in mind
         * that trees with n <= 2 nodes are always balanced)
         */
        if (n > 2)
        {
            tree_node* subtree_root = balanced_binary_tree(n - 1);

            /* try first placing the subtree on the root's left side */
            root = new tree_node;
            root->left = subtree_root;

            assert(num_nodes(root) == n);
            assert(is_balanced_tree(root) == false);

            /* try then placing the subtree on the root's right side */
            root->left = nullptr;
            root->right = subtree_root;

            assert(num_nodes(root) == n);
            assert(is_balanced_tree(root) == false);

            delete root;
        }

        std::cout << "passed tests for trees of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
