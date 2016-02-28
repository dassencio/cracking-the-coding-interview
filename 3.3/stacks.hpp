#ifndef __STACKS_HPP__
#define __STACKS_HPP__

#include <stack>
#include <vector>
#include <cstddef>	/* size_t */
#include <cassert>

template< typename T >
class stacks
{
public:
	stacks(const size_t capacity): capacity_(capacity)
	{
		/* nothing needs to be done here */
	}

	/**
	 * @brief pushes an element onto the last stack if possible,
	 *        otherwise create a new stack for it
	 * @param value the value to push
	 * @note complexity: O(1) in both time and space
	 */
	void push(const T& value)
	{
		if (stack_capacity() == 0)
		{
			return;
		}

		/*
		 * if no stacks have been created yet or if the last stack
		 * is full, create a new stack
		 */
		if (empty() == true || stacks_.back().size() == stack_capacity())
		{
			stacks_.emplace_back();
		}

		stacks_.back().push(value);
	}

	/**
	 * @brief pops an element from the last stack
	 * @note complexity: O(1) in both time and space
	 */
	void pop()
	{
		if (empty() == true)
		{
			return;
		}

		pop_at(num_stacks()-1);
	}

	/**
	 * @brief pops an element from the k-th stack
	 * @note complexity: O(stack capacity) in space, O(n) in time, where
	 *       n is the total number of elements stored
	 */
	void pop_at(size_t k)
	{
		if (empty() == true)
		{
			return;
		}

		assert(k < num_stacks());

		stacks_[k].pop();

		/* as long as we have not reached the last stack */
		while (k+1 < num_stacks())
		{
			std::stack< T > rollover;

			/*
			 * move all elements from the next stack to the
			 * rollover stack except for the bottom one
			 */
			while (stacks_[k+1].size() > 1)
			{
				rollover.push(stacks_[k+1].top());
				stacks_[k+1].pop();
			}

			/*
			 * refill the current stack to its full capacity
			 * using the remaining element on the next stack
			 */
			stacks_[k].push(stacks_[k+1].top());
			stacks_[k+1].pop();

			/*
			 * move all elements from the rollover stack back
			 * to the next stack
			 */
			while (rollover.empty() == false)
			{
				stacks_[k+1].push(rollover.top());
				rollover.pop();
			}

			/* continue the process on the next stack */
			++k;
		}

		/* if the last stack ends up becoming empty, discard it */
		if (stacks_.back().empty() == true)
		{
			stacks_.pop_back();
		}
	}

	/**
	 * @brief returns the element on the top of the last stack
	 * @note complexity: O(1) in both time and space
	 */
	const T& top() const
	{
		assert(empty() == false);

		return stacks_.back().top();
	}

	/**
	 * @brief returns true if no stacks have been created, false otherwise
	 * @note complexity: O(1) in both time and space
	 */
	bool empty() const
	{
		return size() == 0;
	}

	/**
	 * @brief returns the maximum capacity of a single stack
	 * @note complexity: O(1) in both time and space
	 */
	size_t stack_capacity() const
	{
		return capacity_;
	}

	/**
	 * @brief returns the total number of stacks created
	 * @note complexity: O(1) in both time and space
	 */
	size_t num_stacks() const
	{
		return stacks_.size();
	}

	/**
	 * @brief returns the total number of elements over all stacks
	 * @note complexity: O(1) in both time and space
	 */
	size_t size() const
	{
		if (stacks_.empty() == true)
		{
			return 0;
		}

		return (stacks_.size()-1) * stack_capacity()
		       + stacks_.back().size();
	}

private:
	std::vector< std::stack< T > > stacks_;
	size_t capacity_;
};

#endif /* __STACKS_HPP__ */
