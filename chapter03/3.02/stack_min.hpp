#ifndef __STACK_MIN_HPP__
#define __STACK_MIN_HPP__

#include <cassert>

template<typename T>
class stack_min
{
    /* node as a private member structure (we don't need it to be public) */
    struct node
    {
        T value_;
        node* next_node_;
        node* next_min_;
    };

public:
    /**
     * @brief Destructor.
     * @note Complexity: O(n) in time, O(1) in space.
     */
    ~stack_min()
    {
        while (empty() == false)
        {
            pop();
        }
    }

    /**
     * @brief Pushes a value onto the stack.
     * @note Complexity: O(1) in both time and space.
     */
    void push(const T& value)
    {
        node* new_node = new node{.value_ = value, .next_node_ = top_, .next_min_ = min_};

        /*
         * if this is the first node we are pushing onto the stack or
         * if its value is the new stack minimum
         */
        if (empty() == true || value <= min_->value_)
        {
            min_ = new_node;
        }

        top_ = new_node;
    }

    /**
     * @brief Returns the value on the top of the stack.
     * @note Complexity: O(1) in both time and space.
     */
    const T& top() const
    {
        return top_->value_;
    }

    /**
     * @brief Pops the value on the top of the stack.
     * @note Complexity: O(1) in both time and space.
     */
    void pop()
    {
        if (empty())
        {
            return;
        }

        /*
         * if we are deleting the current minimum value on the stack,
         * we must update the stack minimum node pointer
         */
        if (top_ == min_)
        {
            min_ = top_->next_min_;
        }

        node* old_top = top_;
        top_ = top_->next_node_;
        delete old_top;
    }

    /**
     * @brief Returns the minimum value on the stack.
     * @note Complexity: O(1) in both time and space.
     */
    const T& min() const
    {
        assert(top_ != nullptr);
        return min_->value_;
    }

    /**
     * @brief Returns true if the stack is empty, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool empty() const
    {
        return top_ == nullptr;
    }

private:
    node* top_ = nullptr;
    node* min_ = nullptr;
};

#endif /* __STACK_MIN_HPP__ */
