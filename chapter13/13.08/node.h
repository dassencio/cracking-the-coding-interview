#ifndef __NODE_H__
#define __NODE_H__

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

/* node of a directed graph */
class node
{
public:
	node(const size_t __index): index(__index)
	{
		/* nothing needs to be done here */
	}

	/**
	 * @brief destructor: deletes the entire subgraph reachable from this
	 *        node and the node itself
	 * @note complexity: O(m+n) in time, O(n) in space, where m and n are
	 *       the number of edges and vertices in the graph respectively
	 */
	~node()
	{
		std::unordered_set< node* > reachable = get_reachable_nodes();

		for (node* n : reachable)
		{
			/* watch out for self loops */
			if (n != this)
			{
				/*
				 * for each reachable node, clear its neighbor
				 * list before deleting the node itself; if we
				 * did not do this, we could have a deletion cycle
				 */
				n->neighbors.clear();

				delete n;
			}
		}
	}

	/**
	 * @brief creates a directed edge connecting this and other
	 * @note complexity: O(1) in both time and space
	 */
	void connect(node* other)
	{
		neighbors.push_back(other);
	}

	/**
	 * @brief clones the graph and returns a pointer to the node which is
	 *        the copy of this one on the generated graph
	 * @note complexity: O(m+n) in both time and space, where m and n are
	 *       the number of edges and vertices in the graph respectively
	 */
	node* clone() const
	{
		std::unordered_map< const node*, node* > cloned;
		return __clone(this, cloned);
	}

	friend bool equal(const node* n1, const node* n2);

private:
	/**
	 * @brief returns the set of all graph nodes reachable from this node
	 * @note complexity: O(m+n) in time, O(n) in space, where m and n are
	 *       the number of edges and vertices in the graph respectively
	 */
	std::unordered_set< node* > get_reachable_nodes() const
	{
		std::unordered_set< node* > reachable;
		__get_reachable_nodes(reachable);

		return reachable;
	}

	void __get_reachable_nodes(std::unordered_set< node* >& reachable) const
	{
		/* use DFS to find all reachable nodes */
		for (node* n : neighbors)
		{
			/* if we have not yet discovered n */
			if (reachable.find(n) == reachable.end())
			{
				reachable.insert(n);
				n->__get_reachable_nodes(reachable);
			}
		}
	}

	node* __clone(const node* current,
	              std::unordered_map< const node*, node* >& cloned) const
	{
		node* current_cpy = new node(current->index);

		cloned[current] = current_cpy;

		for (const node* n : current->neighbors)
		{
			/* if n has not been cloned yet */
			if (cloned.find(n) == cloned.end())
			{
				current_cpy->neighbors.push_back(__clone(n, cloned));
			}
			else
			{
				current_cpy->neighbors.push_back(cloned[n]);
			}
		}

		return current_cpy;
	}

	friend bool __equal(const node* n1,
	                    const node* n2,
	                    std::unordered_set< const node* >& visited1,
	                    std::unordered_set< const node* >& visited2);

	/* a node can have an arbitrary number of neighbors */
	std::vector< node* > neighbors;
	const size_t index;
};

bool __equal(const node* n1,
             const node* n2,
             std::unordered_set< const node* >& visited1,
             std::unordered_set< const node* >& visited2)
{
	if (n1->index != n2->index)
	{
		return false;
	}

	if (n1->neighbors.size() != n2->neighbors.size())
	{
		return false;
	}

	visited1.insert(n1);
	visited2.insert(n2);

	for (size_t i = 0; i < n1->neighbors.size(); ++i)
	{
		const node* c1 = n1->neighbors[i];
		const node* c2 = n2->neighbors[i];

		auto res1 = visited1.find(c1);
		auto res2 = visited2.find(c2);

		/*
		 * c1 and c2 must have been either both visited or both not yet
		 * visited on their respective graphs, otherwise the graphs are
		 * not equal
		 */
		if ((res1 == visited1.end()) != (res2 == visited2.end()))
		{
			return false;
		}

		/* if both c1 and c2 were not yet visited */
		if (res1 == visited1.end())
		{
			if (__equal(c1, c2, visited1, visited2) == false)
			{
				return false;
			}
		}
	}

	return true;
}

/**
 * @brief returns true if two graphs are equal to each other, false otherwise
 * @note complexity: O(m+n) in both time and space, where m = min(m1,m2) and
 *                   n = min(n1,n2), with m1/m2 and n1/n2 being the number of
 *                   of edges and vertices in the first and second graphs
 *                   respectively
 */
bool equal(const node* n1, const node* n2)
{
	/* nodes visited while traversing graph 1 */
	std::unordered_set< const node* > visited1;

	/* nodes visited while traversing graph 2 */
	std::unordered_set< const node* > visited2;

	return __equal(n1, n2, visited1, visited2);
}

#endif /* __NODE_H__ */
