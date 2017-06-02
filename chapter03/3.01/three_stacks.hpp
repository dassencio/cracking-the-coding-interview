#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cassert>
#include <cstddef>

/*
 * implementation of three stacks stored as a single array of length 3n, with
 * each stack being allowed to store at most n elements
 */
template<typename T>
class three_stacks
{
public:
    /** @brief Constructor for three stacks of maximum size n. */
    three_stacks(const size_t n) : max_stack_size_(n)
    {
        values_ = new T[3 * n];
    }

    /** @brief Destructor. */
    ~three_stacks()
    {
        delete[] values_;
    }

    /**
     * @brief Pushes a value onto the k-th stack.
     * @return true if the value was inserted, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool push(const size_t k, const T& value)
    {
        if (stack_size_[k] == max_stack_size_)
        {
            return false;
        }
        else
        {
            values_[k * max_stack_size_ + stack_size_[k]] = value;
            ++stack_size_[k];
            return true;
        }
    }

    /**
     * @brief Pops a value from the k-th stack.
     * @note Complexity: O(1) in both time and space.
     */
    void pop(const size_t k)
    {
        if (stack_size_[k] == 0)
        {
            return;
        }
        --stack_size_[k];
    }

    /**
     * @brief Returns the value on top of the k-th stack.
     * @note Complexity: O(1) in both time and space.
     */
    T top(const size_t k) const
    {
        assert(empty(k) == false);
        return values_[k * max_stack_size_ + stack_size_[k] - 1];
    }

    /**
     * @brief Returns the number of elements on the k-th stack.
     * @note Complexity: O(1) in both time and space.
     */
    size_t size(const size_t k) const
    {
        return stack_size_[k];
    }

    /**
     * @brief Returns true if the k-th stack is empty, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool empty(const size_t k) const
    {
        return stack_size_[k] == 0;
    }

private:
    T* values_;
    size_t max_stack_size_;
    size_t stack_size_[3] = {0, 0, 0};
};

#endif /* __STACK_HPP__ */
