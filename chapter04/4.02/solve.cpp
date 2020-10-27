/*
 * TASK: Determine whether there is a route between two nodes of a given
 *       directed graph.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <unordered_set>
#include <vector>

/** @brief A directed graph represented by its adjacency list. */
class directed_graph
{
public:
    directed_graph(const size_t n) : adjacency_list_(n)
    {
        /* nothing needs to be done here */
    }

    /**
     * @brief Creates a directed edge connecting node u to node v.
     * @note Complexity: O(1) in both time and space.
     */
    void create_edge(const size_t u, const size_t v)
    {
        adjacency_list_[u].push_back(v);
    }

    /**
     * @brief Returns a list containing the nodes to which node u is connected.
     * @note Complexity: O(1) in both time and space.
     */
    const std::list<size_t>& adjacency_list(const size_t u) const
    {
        return adjacency_list_[u];
    }

private:
    std::vector<std::list<size_t> > adjacency_list_;
};

/**
 * @brief Returns true if a path between nodes s and d exists, false otherwise
 *        (the existence of a path is determined using BFS).
 * @note Complexity: O(m+n) in time, O(n) in space, where m and n are the
 *       number of edges and nodes on the graph respectively.
 */
bool has_path_bfs(const directed_graph& G, const size_t s, const size_t d)
{
    std::queue<size_t> Q;
    std::unordered_set<size_t> explored;

    Q.push(s);
    explored.insert(s);

    while (Q.empty() == false)
    {
        const size_t u = Q.front();
        Q.pop();

        if (u == d)
        {
            return true;
        }

        /* go over the nodes to which u is connected */
        for (const size_t v : G.adjacency_list(u))
        {
            /* if we have not yet explored v */
            if (explored.find(v) == explored.end())
            {
                Q.push(v);
                explored.insert(v);
            }
        }
    }

    return false;
}

bool __has_path_dfs(const directed_graph& G,
                    const size_t s,
                    const size_t d,
                    std::unordered_set<size_t>& explored)
{
    explored.insert(s);

    /* go over the nodes to which s is connected */
    for (const size_t v : G.adjacency_list(s))
    {
        if (v == d)
        {
            return true;
        }

        /* if v was not yet explored */
        if (explored.find(v) == explored.end())
        {
            if (__has_path_dfs(G, v, d, explored) == true)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Returns true if a path between nodes s and d exists, false otherwise
 *        (the existence of a path is determined using DFS).
 * @note Complexity: O(m+n) in time, O(n) in space, where m and n are the
 *       number of edges and nodes on the graph respectively (the space
 *       complexity is O(n) because the recursion will not go deepder than
 *       n levels).
 */
bool has_path_dfs(const directed_graph& G, const size_t s, const size_t d)
{
    /* trivial case: source and destination are the same node */
    if (s == d)
    {
        return true;
    }

    std::unordered_set<size_t> explored;
    return __has_path_dfs(G, s, d, explored);
}

/**
 * @brief Creates a random directed graph with n nodes and m edges.
 * @note Complexity: O(n+m) in both time and space.
 */
directed_graph random_graph(const size_t n, size_t m)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    directed_graph G(n);

    if (n > 0)
    {
        std::uniform_int_distribution<size_t> distribution(0, n - 1);

        while (m > 0)
        {
            size_t u = distribution(generator);
            size_t v = distribution(generator);

            G.create_edge(u, v);
            --m;
        }
    }

    return G;
}

int main()
{
    for (size_t n = 0; n <= 20; ++n)
    {
        for (size_t m = 0; m <= n * n; ++m)
        {
            directed_graph G = random_graph(n, m);

            /*
             * check that both BFS and DFS yield the same
             * results for all pairs of nodes (u,v) in G
             */
            for (size_t u = 0; u < n; ++u)
            {
                for (size_t v = 0; v < n; ++v)
                {
                    assert(has_path_bfs(G, u, v) == has_path_dfs(G, u, v));
                }
            }

            /*
             * sanity check: for all edges u -> v, a path between
             * u and v must exist
             */
            for (size_t u = 0; u < n; ++u)
            {
                for (const size_t v : G.adjacency_list(u))
                {
                    assert(has_path_bfs(G, u, v) == true);
                    assert(has_path_dfs(G, u, v) == true);
                }
            }
        }

        std::cout << "passed random tests for graphs of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
