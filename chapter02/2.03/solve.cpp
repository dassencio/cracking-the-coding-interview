/*
 * TASK: Given a singly-linked list with labeled nodes, e.g., 0 -> 1 -> 2 -> 3
 *       and a pointer to a node on the list which is not the tail node, remove
 *       that node. As an example, on the list above and a pointer to node 2,
 *       we need to  turn the list into 0 -> 1 -> 3.
 */

#include <cassert>
#include <iostream>

/* a simple singly-linked list node */
class list_node
{
public:
    size_t label;
    list_node* next;

    /**
     * @brief Deletes this and the following list nodes.
     * @note Complexity: O(n) in both time and space, where n is the
     *       number of nodes in the list.
     */
    ~list_node()
    {
        delete next;
    }
};

/**
 * @brief Removes a node from a singly-linked list.
 * @note Complexity: O(1) in both time and space.
 */
void delete_node(list_node* node)
{
    /* we should not use this method to delete the tail node */
    assert(node != nullptr && node->next != nullptr);

    list_node* next = node->next;

    node->label = next->label;
    node->next = next->next;

    next->next = nullptr;

    delete next;
}

/**
 * @brief Generates a singly-linked list 0 -> 1 -> ... -> (n-1).
 * @note Complexity: O(n) in both time and space.
 */
list_node* generate_list(size_t n)
{
    list_node* head = nullptr;

    while (n > 0)
    {
        --n;
        list_node* new_node = new list_node{n, head};
        head = new_node;
    }

    return head;
}

int main()
{
    for (size_t n = 2; n <= 100; ++n)
    {
        /*
         * for each i in [0,n-1), generate a list 0 -> 1 -> ... -> (n-1)
         * and delete node i
         */
        for (size_t i = 0; i + 1 < n; ++i)
        {
            list_node* head = generate_list(n);
            list_node* node = head;

            while (node->label != i)
            {
                node = node->next;
            }

            /* delete node i */
            delete_node(node);

            node = head;

            /*
             * check if the resulting list after deleting i is
             * 0 -> ... -> (i-1) -> (i+1) -> ... -> (n-1)
             */
            for (size_t j = 0; j < n; ++j)
            {
                if (j == i)
                {
                    continue;
                }

                assert(node->label == j);
                node = node->next;
            }

            delete head;
        }

        std::cout << "passed tests for lists of length " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
