/*
 * TASK: You are given a circular linked list. Determine the first node at the
 *       beginning of the loop. A circular linked list is one in which a node
 *       n_k points to a node_j for j < k, with n_1 being the head node of the
 *       list. As an example, A -> B -> C -> D -> B is a circular list, and B
 *       is the first node in the loop.
 */

#include <cassert>
#include <iostream>
#include <random>
#include <unordered_set>

/* a simple singly-linked list class */
class list_node
{
public:
    list_node* next = nullptr;

    /**
     * @brief Deletes this and the following list nodes.
     * @note Complexity: O(n) in both time and space, where n is the number of
     *       nodes in the list.
     */
    ~list_node()
    {
        /* special case: node with no following node */
        if (next == nullptr)
        {
            return;
        }

        list_node* current = this;

        /*
         * build a set containing all the following nodes; in the
         * process, set the 'next' field of every node in the list
         * to nullptr so we can delete them later without repeating
         * this task again for every single node
         */
        std::unordered_set<list_node*> nodes = {this};

        while (current != nullptr)
        {
            /* if the list is circular, break the cycle */
            if (nodes.find(current->next) != nodes.end())
            {
                current->next = nullptr;
                break;
            }

            nodes.insert(current->next);
            list_node* next_node = current->next;
            current->next = nullptr;
            current = next_node;
        }

        /* 'this' is already being freed, don't free it again */
        nodes.erase(this);

        for (list_node* node : nodes)
        {
            delete node;
        }
    }
};

/**
 * @brief Detects the starting node of a loop on a circular list.
 * @param head The head of the list.
 * @return A pointer to the node where the loop begins if the list has a loop,
 *         otherwise nullptr.
 * @note Complexity: O(n) in time, O(1) in space, where n is the number of
 *       nodes in the list.
 */
const list_node* get_loop_start_1(const list_node* head)
{
    const list_node* n1 = head;
    const list_node* n2 = head;

    while (n2 != nullptr && n2->next != nullptr)
    {
        /* n2 moves forward twice as fast as n1 */
        n1 = n1->next;
        n2 = n2->next->next;

        /* if n1 meets n2, a loop exists */
        if (n1 == n2)
        {
            break;
        }
    }

    /* if the list does not contain a loop */
    if (n2 == nullptr || n2->next == nullptr)
    {
        return nullptr;
    }

    n1 = head;

    /*
     * a circular loop exists; by moving n1 back to head, n1 and n2
     * are then at the same distance from the beginning of this loop,
     * so advance them until they meet
     */
    while (n1 != n2)
    {
        n1 = n1->next;
        n2 = n2->next;
    }

    return n1;
}

/**
 * @brief Detects the starting node of a loop on a circular list by keeping
 *        a set of seen nodes and detecting duplicates.
 * @param head The head of the list.
 * @return A pointer to the node where the loop begins if the list has a loop,
 *         otherwise nullptr.
 * @note Complexity: O(n) in both time and space, where n is the number of
 *       nodes in the list.
 */
const list_node* get_loop_start_2(const list_node* head)
{
    const list_node* current = head;
    std::unordered_set<const list_node*> seen;

    while (current != nullptr)
    {
        if (seen.find(current) != seen.end())
        {
            return current;
        }

        seen.insert(current);
        current = current->next;
    }

    return nullptr;
}

/**
 * @brief Generates a random list which is circular with 50% probability.
 * @note Complexity: O(n) in both time and space.
 */
list_node* random_list(const size_t n)
{
    if (n == 0)
    {
        return nullptr;
    }

    std::vector<list_node*> nodes;

    list_node* head = nullptr;

    for (size_t i = 0; i < n; ++i)
    {
        list_node* old_head = head;
        head = new list_node;
        head->next = old_head;
        nodes.push_back(head);
    }

    list_node* tail = nodes[0];

    static std::random_device device;
    static std::mt19937 generator(device());

    std::bernoulli_distribution coinflip(0.5);

    /* only make the list circular if a fair coin flip yields "heads" */
    if (coinflip(generator) == true)
    {
        std::uniform_int_distribution<size_t> position(0, n - 1);
        tail->next = nodes[position(generator)];
    }

    return head;
}

int main()
{
    for (size_t n = 0; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            list_node* head = random_list(n);
            assert(get_loop_start_1(head) == get_loop_start_2(head));

            delete head;
        }

        std::cout << "passed random tests for lists of length " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
