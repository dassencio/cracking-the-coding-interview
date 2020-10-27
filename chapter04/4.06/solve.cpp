/*
 * TASK: For a given binary tree and two nodes of this tree, determine their
 *       first common ancestor.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/** @brief A node of a binary tree. */
struct tree_node
{
    tree_node* parent = nullptr;
    tree_node* left = nullptr;
    tree_node* right = nullptr;

    ~tree_node()
    {
        delete left;
        delete right;
    }
};

/**
 * @brief Finds the common ancestor of two nodes n1 and n2 on the same tree.
 * @note Complexity: O(tree height) in time, O(1) in space.
 */
const tree_node* find_common_ancestor_1(const tree_node* n1,
                                        const tree_node* n2)
{
    const tree_node* __n1 = n1;
    const tree_node* __n2 = n2;

    size_t d1 = 0;
    size_t d2 = 0;

    /*
     * determine the distances d1 and d2 between nodes n1 and n2 and the
     * root node respectively (each loop condition means "as long as ni
     * is not the root node...")
     */
    while (n1->parent != nullptr)
    {
        ++d1;
        n1 = n1->parent;
    }
    while (n2->parent != nullptr)
    {
        ++d2;
        n2 = n2->parent;
    }

    n1 = __n1;
    n2 = __n2;

    /*
     * if n1 is farther from the root than n2 (d1 > d2), follow its antecessors
     * until we reach a node at same distance from the root as n2
     */
    while (d1 > d2)
    {
        n1 = n1->parent;
        --d1;
    }

    /*
     * if n2 is farther from the root than n1 (d2 > d1), follow its antecessors
     * until we reach a node at same distance from the root as n1
     */
    while (d2 > d1)
    {
        n2 = n2->parent;
        --d2;
    }

    /*
     * at this stage, both n1 and n2 point to nodes which are equally far
     * from the root node; move one antecessor up at each iteration until
     * we reach a common ancestor
     */
    while (n1->parent != n2->parent)
    {
        n1 = n1->parent;
        n2 = n2->parent;
    }

    return n1->parent;
}

/**
 * @brief Finds the common ancestor of two nodes n1 and n2 on the same tree
 *        using brute force.
 * @note Complexity: O((tree height)²) in time, O(1) in space.
 */
const tree_node* find_common_ancestor_2(const tree_node* n1,
                                        const tree_node* n2)
{
    const tree_node* a1 = n1->parent;

    while (a1 != nullptr)
    {
        const tree_node* a2 = n2->parent;

        while (a2 != nullptr)
        {
            if (a1 == a2)
            {
                return a1;
            }

            a2 = a2->parent;
        }

        a1 = a1->parent;
    }

    return a1;
}

/**
 * @brief Generates a random binary tree with n nodes and returns them as a
 *        vector of nodes, with the first element being the tree's root node.
 * @note Complexity: O(n) in both time and space (on average).
 */
std::vector<tree_node*> random_tree(const size_t n)
{
    if (n == 0)
    {
        return {};
    }

    static std::random_device device;
    static std::mt19937 generator(device());

    std::bernoulli_distribution left_or_right(0.5);

    /* the first generated node is the root */
    std::vector<tree_node*> nodes = {new tree_node};

    while (nodes.size() < n)
    {
        std::uniform_int_distribution<size_t> node_chooser(0, nodes.size() - 1);

        size_t index = node_chooser(generator);
        bool side = left_or_right(generator);

        /* side = true/false if the new node must be a left/right child */
        if (side == true && nodes[index]->left == nullptr)
        {
            nodes.push_back(new tree_node);
            nodes[index]->left = nodes.back();
            nodes.back()->parent = nodes[index];
        }
        else if (side == false && nodes[index]->right == nullptr)
        {
            nodes.push_back(new tree_node);
            nodes[index]->right = nodes.back();
            nodes.back()->parent = nodes[index];
        }
    }

    return nodes;
}

int main()
{
    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<tree_node*> tree_nodes = random_tree(n);

            for (const tree_node* n1 : tree_nodes)
            {
                for (const tree_node* n2 : tree_nodes)
                {
                    const tree_node* a1 = find_common_ancestor_1(n1, n2);
                    const tree_node* a2 = find_common_ancestor_2(n1, n2);

                    assert(a1 == a2);
                }
            }

            if (n > 0)
            {
                delete tree_nodes.front();
            }
        }

        std::cout << "passed random tests for trees of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
