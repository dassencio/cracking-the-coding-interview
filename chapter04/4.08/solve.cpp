/*
 * TASK: For a given binary tree whose keys are integer values and an integer
 *       value V, determine all paths in the tree such that the sum of their
 *       keys is V. Here, a tree path is any downward list of nodes, i.e., the
 *       first node in the path is the one closest to root, and every edge on
 *       a path must point away from the root (it goes always from a parent
 *       node to one of its children nodes).
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
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

using path = std::list<const tree_node*>;

/**
 * @brief Determines all tree paths which sum to a given value.
 * @param last_node A node in the tree at which a path must end.
 * @param total The value to which a tree path must sum.
 * @param paths The vector on which the paths which sum to total will be
 *        written.
 * @note Complexity: O(n³) in both time and space, where n is the number of
 *       tree nodes (consider the case in which the tree is a single path
 *       node_1 -> node_2 -> ... -> node_n, with node_1 being the root node;
 *       in this case, the work done for node_k [including memory allocation]
 *       is O(k²) if all keys are zero and total = zero), but if we only
 *       wanted to print the paths which sum to total, the complexity would
 *       be only O(n²) in time and O(n) in space.
 */
void get_paths_which_sum_to(const tree_node* last_node,
                            const int total,
                            std::vector<path>& paths)
{
    if (last_node == nullptr)
    {
        return;
    }

    int sum_so_far = 0;

    path current_path;
    const tree_node* current = last_node;

    while (current != nullptr)
    {
        sum_so_far += current->key;
        current_path.push_front(current);

        if (sum_so_far == total)
        {
            paths.push_back(current_path);
        }

        current = current->parent;
    }

    get_paths_which_sum_to(last_node->left, total, paths);
    get_paths_which_sum_to(last_node->right, total, paths);
}

/**
 * @brief Determines all paths in a tree.
 * @param last_node A node in the tree at which a path must end.
 * @param paths The vector on which the determined paths will be written.
 * @note Complexity: O(n³) in both time and space, where n is the number of
 *       tree nodes (consider the case in which the tree is a single path
 *       node_1 -> node_2 -> ... -> node_n, with node_1 being the root node;
 *       in this case, the work done for node_k [including memory allocation]
 *       is O(k²)).
 */
void get_all_tree_paths(const tree_node* last_node, std::vector<path>& paths)
{
    if (last_node == nullptr)
    {
        return;
    }

    path current_path;
    const tree_node* current = last_node;

    while (current != nullptr)
    {
        current_path.push_front(current);
        paths.push_back(current_path);
        current = current->parent;
    }

    get_all_tree_paths(last_node->left, paths);
    get_all_tree_paths(last_node->right, paths);
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

/**
 * @brief Computes the sum of the keys from all nodes in a path.
 * @note Complexity: O(k) in time, O(1) in space, where k is the path length.
 */
int path_sum(const path& nodes)
{
    int total = 0;

    for (const tree_node* node : nodes)
    {
        total += node->key;
    }

    return total;
}

int main()
{
    for (int n = 0; n <= 20; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::vector<tree_node*> tree_nodes = random_tree(n);

            int sum_positives = 0;
            int sum_negatives = 0;

            for (const tree_node* node : tree_nodes)
            {
                sum_positives += (node->key > 0) ? node->key : 0;
                sum_negatives += (node->key < 0) ? node->key : 0;
            }

            const tree_node* root = (n > 0) ? tree_nodes.front() : nullptr;

            std::vector<path> all_paths;
            get_all_tree_paths(root, all_paths);

            for (int total = sum_negatives; total <= sum_positives; ++total)
            {
                std::vector<path> sum_paths;
                get_paths_which_sum_to(root, total, sum_paths);

                for (const path& p : all_paths)
                {
                    if (path_sum(p) == total)
                    {
                        assert(std::find(sum_paths.begin(),
                                         sum_paths.end(),
                                         p) != sum_paths.end());
                    }
                }
            }

            delete root;
        }

        std::cout << "passed random tests for trees of size " << n << std::endl;
    }
}
