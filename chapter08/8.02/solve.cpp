/*
 * TASK: Imagine an n×n grid in which a robot is placed at the top-left cell.
 *       The robot is supposed to move to the bottom-right cell of the grid,
 *       but it can only do so by moving either to its right grid cell or to its
 *       bottom grid cell at each motion step. What is the number of possible
 *       paths which the robot can take to reach its goal? Try solving the
 *       problem also when some cells are turned into obstacles (i.e., the robot
 *       cannot go on top of them).
 *
 * NOTE: In the solution below, we assume that the top-left corner cell of the
 *       grid has indices (n-1,n-1), and the robot's goal is to get to the
 *       bottom-right grid cell which is at (0,0). In other words, x indices
 *       decrease as we move to the right on the grid and y indices decrease as
 *       we move down.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <random>
#include <vector>

/** @brief A grid cell represented as a pair of indices (x,y). */
struct position
{
    const size_t x;
    const size_t y;
};

using path = std::list<position>;

/*
 * obstacles are represented as a matrix whose indices represent grid cells,
 * so a cell (x,y) is an obstacle if its associated matrix entry is "true",
 * otherwise it is free and can be occupied by the robot
 */
using obstacles = std::vector<std::vector<bool> >;

/**
 * @brief Computes all valid paths from position (x,y) to position (0,0) on a
 *        grid given a set of obstacles.
 * @param x The index of the grid column where the robot is initially located.
 * @param y The index of the grid row where the robot is initially located.
 * @param O A matrix representing the state of each grid cell (obstacle/free).
 * @return A list containing all valid paths from (x,y) to (0,0).
 * @note Complexity: O((x+y+1)! / (x!*y!) in both time and space because each
 *       computed path has length x+y+1.
 */
std::list<path> compute_all_paths(const size_t x,
                                  const size_t y,
                                  const obstacles& O)
{
    /* if we reached the bottom-right grid cell */
    if (x == 0 && y == 0)
    {
        return {path{position{0, 0}}};
    }

    std::list<path> paths;

    /* get all valid paths which start by going down from (x,y) */
    if (y > 0 && O[x][y - 1] == false)
    {
        paths.splice(paths.end(), compute_all_paths(x, y - 1, O));
    }

    /* get all valid paths which start by going right from (x,y) */
    if (x > 0 && O[x - 1][y] == false)
    {
        paths.splice(paths.end(), compute_all_paths(x - 1, y, O));
    }

    /* now add (x,y) as the starting position for all paths above */
    for (path& p : paths)
    {
        p.push_front(position{x, y});
    }

    return paths;
}

/**
 * @brief Returns true if a given path is valid on a grid which may contain
 *        obstacles, false otherwise.
 * @param p A path (list of positions on the grid).
 * @param n The grid size.
 * @param O A matrix representing the state of each grid cell (obstacle/free).
 * @note Complexity: O(n) in time, O(1) in space.
 */
bool is_valid_path(const path& p, const size_t n, const obstacles& O)
{
    /*
     * the total number of moves on a valid path is 2*(n-1), so the path
     * must have 2*(n-1) + 1 = 2*n-1 positions
     */
    if (p.size() != 2 * n - 1)
    {
        return false;
    }

    auto it_current = p.begin();

    /* the first position on the path must be the top-left cell (n-1,n-1) */
    if (it_current->x != n - 1 || it_current->y != n - 1)
    {
        return false;
    }

    auto it_next = std::next(it_current);

    while (it_next != p.end())
    {
        const position& current = *it_current;
        const position& next = *it_next;

        /* if we are on top of an obstacle, the path is invalid */
        if (O[current.x][current.y] == true)
        {
            return false;
        }

        /*
         * if the next grid cell is not either below or to the right of
         * the current cell, the solution is invalid
         */
        if (!(current.x == next.x && current.y == next.y + 1) &&
            !(current.x == next.x + 1 && next.y == current.y))
        {
            return false;
        }

        ++it_current;
        ++it_next;
    }

    /* the last position on the path must be the bottom-right cell (0,0) */
    return (it_current->x == 0 && it_current->y == 0);
}

/**
 * @brief Returns n!.
 */
size_t factorial(const size_t n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

/**
 * @brief Returns the number of valid paths for a grid of size n×n when no
 *        obstacles are present (i.e., all cells are free).
 */
size_t num_valid_paths_no_obstacles(const size_t n)
{
    return factorial(2 * (n - 1)) / (factorial(n - 1) * factorial(n - 1));
}

/**
 * @brief Generates an obstacle matrix representing k randomly placed obstacles
 *        on an n×n grid, where the top-left cell is always free.
 * @param n The grid size.
 * @param k The number of obstacles to place on the grid.
 * @note Complexity: O(n²) in time, O(n²) in space if k = O(n).
 */
obstacles random_obstacles(const size_t n, size_t k)
{
    assert(k < n * n);

    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<size_t> distribution(0, n - 1);

    obstacles O(n, std::vector<bool>(n, false));

    while (k > 0)
    {
        size_t x = distribution(generator);
        size_t y = distribution(generator);

        /* the top-left grid cell must always be free */
        if (!(x == n - 1 && y == n - 1) && O[x][y] == false)
        {
            O[x][y] = true;
            --k;
        }
    }

    return O;
}

int main()
{
    for (size_t n = 1; n <= 10; ++n)
    {
        for (size_t k = 0; k < n; ++k)
        {
            obstacles O = random_obstacles(n, k);

            std::list<path> paths = compute_all_paths(n - 1, n - 1, O);

            if (k == 0)
            {
                assert(paths.size() == num_valid_paths_no_obstacles(n));
            }

            for (const path& p : paths)
            {
                assert(is_valid_path(p, n, O));
            }
        }

        std::cout << "passed random tests for grids of size " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
