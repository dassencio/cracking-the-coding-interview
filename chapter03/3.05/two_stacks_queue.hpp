#ifndef __TWO_STACKS_QUEUE_HPP__
#define __TWO_STACKS_QUEUE_HPP__

#include <cassert>
#include <cstddef>
#include <stack>

/**
 * @brief A queue implementation using two stacks: one holds the back end of the
 *        queue, the other holds the front end of the queue; whenever one end
 *        becomes empty and an element needs to be accessed there, the elements
 *        from the other end are moved to the empty one.
 */
template<typename T>
class two_stacks_queue
{
public:
    /**
     * @brief Pushes a value onto the back of the queue.
     * @note Complexity: O(1) in both time and space.
     */
    void push(const T& value)
    {
        back_.push(value);
    }

    /**
     * @brief Returns the value on the front of the queue.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
     *       of elements in the queue.
     */
    const T& front()
    {
        assert(empty() == false);

        if (front_.empty() == true)
        {
            transfer_elements(back_, front_);
        }

        return front_.top();
    }

    /**
     * @brief Returns the value on the back of the queue.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
     *       of elements in the queue.
     */
    const T& back()
    {
        assert(empty() == false);

        if (back_.empty() == true)
        {
            transfer_elements(front_, back_);
        }

        return back_.top();
    }

    /**
     * @brief Pops an element from the front of the queue.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
     *       of elements in the queue.
     */
    void pop()
    {
        assert(empty() == false);

        if (front_.empty() == true)
        {
            transfer_elements(back_, front_);
        }

        front_.pop();
    }

    /**
     * @brief Returns the number of elements in the queue.
     * @note Complexity: O(1) in both time and space.
     */
    size_t size() const
    {
        return front_.size() + back_.size();
    }

    /**
     * @brief Returns true if the queue is empty, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool empty() const
    {
        return size() == 0;
    }

private:
    /**
     * @brief Transfers all elements from stack src to stack dst.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
     *       of elements in the queue.
     */
    void transfer_elements(std::stack<T>& src, std::stack<T>& dst)
    {
        while (src.empty() == false)
        {
            dst.push(src.top());
            src.pop();
        }
    }

    std::stack<T> front_;
    std::stack<T> back_;
};

#endif /* __TWO_STACKS_QUEUE_HPP__ */
