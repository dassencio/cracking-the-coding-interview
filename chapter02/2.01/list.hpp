#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <unordered_set>

/** @brief A singly-linked list. */
template<typename T>
class list
{
private:
    /** @brief A node of a singly-linked list. */
    struct node
    {
        T value_;
        node* next_ = nullptr;
    };

public:
    /**
     * @brief Destructor.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
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
     * @brief Removes duplicates using a buffer (set) with "seen values".
     * @note Complexity: O(n) in both time and space, where n is the number
     *       of nodes in the list.
     * @return The number of removed nodes.
     */
    size_t remove_duplicates_1()
    {
        /* a list needs at least two elements for any removal to occur */
        if (size() <= 1)
        {
            return 0;
        }

        size_t removed = 0;

        std::unordered_set<T> seen;
        seen.insert(head_->value_);

        node* position = head_;

        /*
         * always look at the next node and see if it contains a value
         * already present in [head..position]; if yes, remove the next
         * node and advance
         */
        while (position->next_ != nullptr)
        {
            /* if the next value is a duplicate */
            if (seen.find(position->next_->value_) != seen.end())
            {
                node* node_to_delete = position->next_;
                position->next_ = position->next_->next_;
                delete node_to_delete;

                ++removed;
                --size_;
            }
            else
            {
                seen.insert(position->next_->value_);
                position = position->next_;
            }
        }

        return removed;
    }

    /**
     * @brief Removes all duplicates without using an extra buffer.
     * @note Complexity: O(n²) in time, O(1) in space, where n is the number
     *       of nodes in the list.
     */
    size_t remove_duplicates_2()
    {
        /* a list needs at least two elements for any removal to occur */
        if (size() <= 1)
        {
            return 0;
        }

        size_t removed = 0;

        node* position = head_;

        /*
         * look at all the nodes in [head..position], see if
         * any of them contains the value of the next node;
         * if yes, remove the next node and advance
         */
        while (position->next_ != nullptr)
        {
            node* seen = head_;
            while (seen != position->next_)
            {
                /* the next node is a duplicate; delete it */
                if (seen->value_ == position->next_->value_)
                {
                    node* node_to_delete = position->next_;
                    position->next_ = position->next_->next_;
                    delete node_to_delete;

                    ++removed;
                    --size_;

                    break;
                }
                seen = seen->next_;
            }

            /* if no node was removed */
            if (seen == position->next_)
            {
                position = position->next_;
            }
        }

        return removed;
    }

    /** @brief Returns the list size. */
    size_t size() const
    {
        return size_;
    }

    /**
     * @brief Returns the number of occurrences of a value in the list.
     * @param value The value to search for.
     * @note Complexity: O(n) in time, O(1) in space, where n is the number
     *       of nodes in the list.
     */
    size_t count(const T& value) const
    {
        size_t result = 0;
        node* position = head_;

        while (position != nullptr)
        {
            if (position->value_ == value)
            {
                ++result;
            }
            position = position->next_;
        }

        return result;
    }

private:
    node* head_ = nullptr;
    size_t size_ = 0;
};

#endif /* __LIST_HPP__ */
