#ifndef __BINARY_SEARCH_TREE_HPP__
#define __BINARY_SEARCH_TREE_HPP__

#include <list>
#include <vector>
#include <queue>
#include <unordered_set>

/* a simple binary search tree class */
template< typename T >
class binary_search_tree
{
	/* node as a private member structure (we don't need it to be public) */
	struct tree_node
	{
		T key;

		tree_node* left  = nullptr;
		tree_node* right = nullptr;

		~tree_node()
		{
			delete left;
			delete right;
		}
	};

public:
	/**
	 * @brief empty constructor
	 * @note complexity: O(1) in both time and space
	 */
	binary_search_tree()
	{
		/* nothing needs to be done here */
	}

	/**
	 * @brief destructor
	 * @note complexity: O(n) in both time and space, where n is the number
	 *       of tree nodes, because the recursion will not go deeper than n
	 *       levels
	 */
	~binary_search_tree()
	{
		delete root_;
	}

	/**
	 * @brief inserts an element into the binary tree
	 * @note complexity: O(n) in time, O(1) in space, where n is the number
	 *       of tree nodes
	 */
	void insert(const T& key)
	{
		/* if the tree does not have a root node yet */
		if (root_ == nullptr)
		{
			/* create it and leave */
			root_ = new tree_node;
			root_->key = key;
			++num_elements_;
			return;
		}

		tree_node* current = root_;

		while (true)
		{
			/* if key should be to the left of current */
			if (key <= current->key)
			{
				if (current->left != nullptr)
				{
					current = current->left;
					continue;
				}

				/* current has no left child, insert key there */
				current->left = new tree_node;
				current->left->key = key;
				++num_elements_;
				return;
			}
			/* if key should be to the right of current */
			else
			{
				if (current->right != nullptr)
				{
					current = current->right;
					continue;
				}

				/* current has no right child, insert key there */
				current->right = new tree_node;
				current->right->key = key;
				++num_elements_;
				return;
			}
		}
	}

	/**
	 * @brief returns the number of elements stored on the tree
	 * @note complexity: O(1) in both time and space
	 */
	size_t size() const
	{
		return num_elements_;
	}

	/**
	 * @brief returns the tree height
	 * @note complexity: O(n) in both time and space, where n is the number
	 *       of tree nodes, because the recursion will not go deeper than n
	 *       levels
	 */
	size_t height() const
	{
		return height(root_);
	}

	/**
	 * @brief returns a vector of lists which contain the keys of the nodes
	 *        at each level of the tree (using BFS)
	 * @note complexity: O(n) in both time and space, where n is the number
	 *       of nodes in the tree
	 */
	std::vector< std::list< T > > level_node_list_bfs() const
	{
		if (root_ == nullptr)
		{
			return {};
		}

		std::vector< std::list< T > > node_lists;

		std::queue< tree_node*  > Q;

		/* nullptr is used as a dummy to indicate the end of a level */
		Q.push(root_);
		Q.push(nullptr);

		auto level_list = node_lists.insert(node_lists.end(), std::list< T >{});

		while (Q.empty() == false)
		{
			tree_node* current = Q.front();
			Q.pop();

			/* if we are finishing a level of the tree */
			if (current == nullptr)
			{
				/* if this was the last dummy, we're done */
				if (Q.empty() == true)
				{
					break;
				}
				/* otherwise, we have entered a new tree level */
				else
				{
					Q.push(nullptr);
					level_list = node_lists.insert(node_lists.end(),
					                               std::list< T >{});
				}
			}
			else
			{
				level_list->push_back(current->key);

				if (current->left != nullptr)
				{
					Q.push(current->left);
				}
				if (current->right != nullptr)
				{
					Q.push(current->right);
				}
			}
		}

		return node_lists;
	}

	/**
	 * @brief returns a vector of lists which contain the keys of the nodes
	 *        at each level of the tree (using DFS)
	 * @note complexity: O(n) in both time and space, where n is the number
	 *       of nodes in the tree
	 */
	std::vector< std::list< T > > level_node_list_dfs() const
	{
		return level_node_list_dfs(root_);
	}

private:
	size_t height(const tree_node* current) const
	{
		if (current == nullptr)
		{
			return 0;
		}

		return 1 + std::max(height(current->left), height(current->right));
	}

	std::vector< std::list< T > > level_node_list_dfs(const tree_node* current) const
	{
		if (current == nullptr)
		{
			return {};
		}

		std::vector< std::list< T > > node_lists;

		/*
		 * the topmost level of the subtree with 'current' as root
		 * has a single node: 'current' itself
		 */
		node_lists.push_back({ current->key });

		/*
		 * solve the problem separately for current's left and child
		 * subtrees, then merge the results into a single vector of
		 * (key) lists
		 */
		std::vector< std::list< T > > node_list_left = level_node_list_dfs(current->left);
		std::vector< std::list< T > > node_list_right = level_node_list_dfs(current->right);

		auto it_left  = node_list_left.begin();
		auto it_right = node_list_right.begin();

		while (it_left != node_list_left.end() || it_right != node_list_right.end())
		{
			auto level_list = node_lists.insert(node_lists.end(), std::list< T >{});

			/*
			 * move all elements in the current level to the full level
			 * list; complexity: O(1) in both time and space
			 */
			if (it_left != node_list_left.end())
			{
				level_list->splice(level_list->end(), *it_left);
				++it_left;
			}
			if (it_right != node_list_right.end())
			{
				level_list->splice(level_list->end(), *it_right);
				++it_right;
			}
		}

		return node_lists;
	}

	tree_node* root_ = nullptr;
	size_t num_elements_ = 0;
};


#endif /* __BINARY_SEARCH_TREE_HPP__ */
