#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <cassert>
#include <cstddef>

/* a simple list class */
template<typename T>
class list
{
private:
    /* node as a private member structure (we don't need it to be public) */
    struct node
    {
        T value_;
        node* next_ = nullptr;
    };

public:
    /**
     * @brief Destructor.
     * @note Complexity: O(m) in time, O(1) in space, where m is the number
     *       of nodes in the list.
     */
    ~list()
    {
        node* position = head_;

        while (position != nullptr)
        {
            node* node_to_delete = position;
            position = position->next_;
            delete node_to_delete;
        }
    }

    /**
     * @brief Inserts a new node on the list.
     * @param value The value of the inserted node.
     * @note Complexity: O(1) in both time and space.
     */
    void insert(const T& value)
    {
        node* old_head = head_;
        head_ = new node;
        head_->value_ = value;
        head_->next_ = old_head;

        ++size_;
    }

    /**
     * @brief Returns the n-th to last value in the list, with n = 0
     *        meaning the last value in the list.
     * @note Complexity: O(m) in time, O(1) in space, where m is the number
     *       of nodes in the list.
     */
    const T& get_nth_to_last(const size_t n)
    {
        assert(n < size_);

        node* left = head_;
        node* right = head_;

        /* make right = left + n */
        for (size_t i = 0; i < n; ++i)
        {
            right = right->next_;
        }

        /*
         * advance left and right until right is the last element,
         * then left = right - n will be the n-th to last element!
         */
        while (right->next_ != nullptr)
        {
            left = left->next_;
            right = right->next_;
        }

        return left->value_;
    }

    /** @brief Returns the list size. */
    size_t size() const
    {
        return size_;
    }

private:
    node* head_ = nullptr;
    size_t size_ = 0;
};

#endif /* __LIST_HPP__ */
