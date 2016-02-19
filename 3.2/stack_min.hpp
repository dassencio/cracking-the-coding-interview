#ifndef __STACK_MIN_HPP__
#define __STACK_MIN_HPP__

#include <cassert>

template< typename T >
class stack_min
{
	/* node as a private member structure (we don't need it to be public) */
	struct stack_node
	{
		T value_;
		stack_node* next_node_;
		stack_node* next_min_;
	};

	typedef stack_node* node_pointer;

public:
	/**
	 * @brief destructor
	 * @note complexity: O(n) in time, O(1) in space
	 */
	~stack_min()
	{
		while (empty() == false)
		{
			pop();
		}
	}

	/**
	 * @brief pushes a value onto the stack
	 * @note complexity: O(1) in both time and space
	 */
	void push(const T& value)
	{
		node_pointer new_node = new stack_node{
			.value_ = value,
			.next_node_ = stack_top_,
			.next_min_ = stack_min_
		};

		/*
		 * if this is the first node we are pushing onto the stack or
		 * if its value is the new stack minimum
		 */
		if (empty() == true || value < stack_min_->value_)
		{
			stack_min_ = new_node;
		}

		stack_top_ = new_node;
	}

	/**
	 * @brief returns the value on the top of the stack
	 * @note complexity: O(1) in both time and space
	 */
	const T& top() const
	{
		return stack_top_->value_;
	}

	/**
	 * @brief pops the value on the top of the stack
	 * @note complexity: O(1) in both time and space
	 */
	void pop()
	{
		if (empty())
		{
			return;
		}

		/*
		 * if we are deleting the current minimum value in the stack,
		 * we must update the stack minimum node pointer
		 */
		if (stack_top_ == stack_min_)
		{
			stack_min_ = stack_top_->next_min_;
		}

		node_pointer old_stack_top = stack_top_;
		stack_top_ = stack_top_->next_node_;
		delete old_stack_top;
	}

	/**
	 * @brief returns the minimum value on the stack
	 * @note complexity: O(1) in both time and space
	 */
	const T& min() const
	{
		assert(stack_top_ != nullptr);
		return stack_min_->value_;
	}

	/**
	 * @brief returns true if the stack is empty, false otherwise
	 * @note complexity: O(1) in both time and space
	 */
	bool empty() const
	{
		return stack_top_ == nullptr;
	}

private:
	node_pointer stack_top_ = nullptr;
	node_pointer stack_min_ = nullptr;
};

#endif /* __STACK_MIN_HPP__ */
