/*
 * TASK: Suppose you have a very large binary tree T1 (e.g. containing millions
 *       of nodes) and a small binary tree T2 (e.g. containing a few hundred
 *       nodes). Determine if T2 is a subtree of T1.
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
    tree_node* parent = nullptr;

    ~tree_node()
    {
        delete left;
        delete right;
    }
};

/**
 * @brief Determines whether a tree T2 is a subtree of a tree T1, with both
 *        trees having the same root node.
 * @param root1 The root node of T1.
 * @param root2 The root node of T2.
 * @return true if T2 is a subtree of T1, false otherwise.
 * @note Complexity: O(min(n1,n2)) in time and space, where n1 and n2 are the
 *       number of nodes in T1 and T2 respectively, because the recursion will
 *       not go deeper than O(min(n1,n2)) levels.
 */
bool is_root_subtree(const tree_node* root1, const tree_node* root2)
{
    /* if T2 is empty, it is a subtree of T1 */
    if (root2 == nullptr)
    {
        return true;
    }

    /* T2 is not empty, so if T1 is empty, T2 cannot be a subtree of T1 */
    if (root1 == nullptr)
    {
        return false;
    }

    if (root1->key == root2->key)
    {
        return is_root_subtree(root1->left, root2->left) &&
               is_root_subtree(root1->right, root2->right);
    }

    return false;
}

/**
 * @brief Determines whether a tree T2 is a subtree of a tree T1.
 * @param root1 The root node of T1.
 * @param root2 The root node of T2.
 * @return true if T2 is a subtree of T1, false otherwise.
 * @note Complexity: O(n1*n2) in time and space, where n1 and n2 are the number
 *       of nodes in T1 and T2 respectively, because the recursion will not go
 *       deeper than O(n1*n2) levels.
 */
bool is_subtree(const tree_node* root1, const tree_node* root2)
{
    /* if T1 is empty, T2 can only be a subtree T1 if it is also empty */
    if (root1 == nullptr)
    {
        return (root2 == nullptr);
    }

    return is_root_subtree(root1, root2) || is_subtree(root1->left, root2) ||
           is_subtree(root1->right, root2);
}

/**
 * @brief Generates a random binary tree with n nodes and returns them as a
 *        vector of nodes, with the first element being the tree's root node.
 * @note Complexity: O(n) in both time and space (on average).
 */
std::vector<tree_node*> random_tree(int n)
{
    if (n == 0)
    {
        return {};
    }

    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> key_chooser(-n, n);
    std::bernoulli_distribution left_or_right(0.5);

    /* the first generated node is the root */
    tree_node* root = new tree_node;
    root->key = key_chooser(generator);
    std::vector<tree_node*> nodes = {root};
    --n;

    while (n > 0)
    {
        std::uniform_int_distribution<size_t> node_chooser(0, nodes.size() - 1);

        size_t index = node_chooser(generator);
        bool side = left_or_right(generator);

        /* side = true/false if the new node must be a left/right child */
        if (side == true && nodes[index]->left == nullptr)
        {
            tree_node* new_node = new tree_node;
            new_node->key = key_chooser(generator);
            nodes[index]->left = new_node;
            new_node->parent = nodes[index];
            nodes.push_back(new_node);
            --n;
        }
        else if (side == false && nodes[index]->right == nullptr)
        {
            tree_node* new_node = new tree_node;
            new_node->key = key_chooser(generator);
            nodes[index]->right = new_node;
            new_node->parent = nodes[index];
            nodes.push_back(new_node);
            --n;
        }
    }

    return nodes;
}

int main()
{
    for (int n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<tree_node*> tree_nodes = random_tree(n);

            const tree_node* root = (n > 0) ? tree_nodes.front() : nullptr;

            for (const tree_node* current : tree_nodes)
            {
                assert(is_subtree(root, current) == true);

                if (current != root)
                {
                    assert(is_subtree(current, root) == false);
                }

                tree_node* not_in_tree = new tree_node;
                not_in_tree->key = std::numeric_limits<int>::max();
                assert(is_subtree(root, not_in_tree) == false);

                delete not_in_tree;
            }

            delete root;
        }

        std::cout << "passed random tests for trees of size " << n << std::endl;
    }
}
