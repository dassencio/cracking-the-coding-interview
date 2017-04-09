/*
 * TASK: Given an array of strings with length <= n and a string str of length
 *       n, determine which strings in the input array are substrings of str;
 *       for each string which is a substring of str, determine the position in
 *       str at which it appears.
 */

#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <cassert>

/**
 * @brief basic suffix tree class for solving the "string search" problem;
 *        here the string which generates the suffix tree is assumed to have
 *        length n
 */
class suffix_tree
{
	/**
	 * @brief tree node: contains pointers to its children and all the
	 *        locations at which the character sequence root...node appears
	 *        on the original string (the root node itself represents the
	 *        empty string "")
	 */
	struct node
	{
		~node()
		{
			for (auto& child : children)
			{
				delete child.second;
			}
		}

		std::unordered_map< char, node* > children;
		std::vector< size_t > locations;
		char symbol = '\0';
	};

public:
	/**
	 * @brief constructor with generator string
	 * @note complexity: O(n²) in both time and space
	 */
	suffix_tree(const std::string& str): root(new node)
	{
		/* insert all substrings str[m..n) into the tree for m = 0..n */
		for (size_t i = 0; i < str.size(); ++i)
		{
			insert(str.substr(i, std::string::npos), i);
		}

		/* the empty string appears before and after every character */
		for (size_t i = 0; i <= str.size(); ++i)
		{
			root->locations.push_back(i);
		}
	}

	/**
	 * @brief destructor
	 * @note complexity: O(n) in space, O(n²) in time
	 */
	~suffix_tree()
	{
		delete root;
	}

	/**
	 * @brief returns an array containing all locations at which a string
	 *        str appears in the string which generated the tree
	 * @note complexity: O(1) in space, O(n) in time
	 */
	std::vector< size_t > find(const std::string& str) const
	{
		node* current = root;

		for (const char c : str)
		{
			auto it = current->children.find(c);

			if (it == current->children.end())
			{
				return {};
			}
			else
			{
				current = it->second;
			}
		}

		return current->locations;
	}

private:

	/**
	 * @brief inserts a string substr into the suffix tree, where substr is
	 *        a substring of the string which is currently generating the
	 *        tree starting at the position 'start'
	 * @note complexity: O(n) in both time and space
	 */
	void insert(const std::string& substr, const size_t start)
	{
		node* current = root;

		for (const char c : substr)
		{
			auto it = current->children.find(c);

			if (it == current->children.end())
			{
				node* new_node = new node;
				new_node->symbol = c;
				current->children[c] = new_node;
				current = new_node;
			}
			else
			{
				current = it->second;
			}

			current->locations.push_back(start);
		}
	}

	/* the root node represents the empty string "" */
	node* root;
};

/**
 * @brief generates a random string of length n and characters in [a-d]
 * @note complexity: O(n) in both time and space
 */
std::string random_string(const size_t n)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	std::uniform_int_distribution< char > distribution('a','d');

	std::string str;

	while (str.size() < n)
	{
		str.push_back(distribution(generator));
	}

	return str;
}

/**
 * @brief returns an array containing all locations where a string str1 appears
 *        in another string str2
 * @note complexity: O(n²) in time, O(n) in space, where n is the length of str2
 */
std::vector< size_t > find_occurrences(const std::string& str1,
                                       const std::string& str2)
{
	std::vector< size_t > locations;

	size_t current = 0;
	size_t next = str2.find(str1, current);

	while (next != std::string::npos)
	{
		locations.push_back(next);
		current = next + 1;
		next = str2.find(str1, current);
	}

	return locations;
}

/**
 * @brief returns an array containing all non-empty substrings of a string str
 * @note complexity: O(n²) in time, O(n³) in space, where n is the length of str
 */
std::vector< std::string > substrings(const std::string& str)
{
	std::vector< std::string > substr;

	for (size_t i = 0; i < str.size(); ++i)
	{
		for (size_t j = i; j < str.size(); ++j)
		{
			substr.push_back(str.substr(i, j-i+1));
		}
	}

	return substr;
}

int main()
{
	for (size_t n = 0; n <= 20; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::string str = random_string(n);

			suffix_tree S(str);

			for (const std::string& substr : substrings(str))
			{
				assert(S.find(substr) == find_occurrences(substr, str));
			}

			/* search for random strings in str */
			for (size_t m = 0; m <= n; ++m)
			{
				std::string rnd_str = random_string(m);
				assert(S.find(rnd_str) == find_occurrences(rnd_str, str));
			}
		}

		std::cout << "passed random tests for strings of length " << n << std::endl;
	}

	return EXIT_SUCCESS;
}
