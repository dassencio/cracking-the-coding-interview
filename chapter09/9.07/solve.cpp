/*
 * TASK: For a given group of people, determine what is the tower with the most
 *       number of people which they can form such that each person can stand
 *       on the shoulders of another one only if he/she is both lighter and
 *       smaller than the person below. As an example, a person of height 160cm
 *       and weight 65kg can stand on the shoulders of a person of height 170cm
 *       and weight 70kg but not on the shoulders of someone of weight 60kg or
 *       height 160cm.
 */

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

struct person
{
    int height;
    int weight;
};

/* group represents an arbitrary group of people */
using group = std::vector<person>;

/*
 * tower represents a valid tower of people, with the first element being the
 * person on the base and the last one being the person at the top
 */
using tower = std::deque<person>;

/**
 * @brief Determines the highest tower which can be formed for a group of people
 *        using recursion.
 * @param people A group of people which can be used to form the tower.
 * @param max_weight Weight which the person at the base may not have or exceed.
 * @param max_height Height which the person at the base may not have or exceed.
 * @note Complexity: O(n!) in time, O(n²) in space, where n is the total number
 *       of people available, because at each recursion level, groups of O(n)
 *       people are formed and the recursion does not go deeper than n levels.
 */
tower highest_tower_1(const group& people,
                      const int max_weight = std::numeric_limits<int>::max(),
                      const int max_height = std::numeric_limits<int>::max())
{
    if (people.empty() == true)
    {
        return {};
    }

    tower highest;

    /*
     * for each person i, consider the case in which this person is at the
     * base of the tower and then recurse
     */
    for (size_t i = 0; i < people.size(); ++i)
    {
        /* if the i-th person is within the limits for weight and height */
        if (people[i].weight < max_weight && people[i].height < max_height)
        {
            /* create a group containing all people except i */
            group people_without_i;

            for (size_t j = 0; j < people.size(); ++j)
            {
                if (i != j)
                {
                    people_without_i.push_back(people[j]);
                }
            }

            /*
             * compute the highest possible tower which can be put
             * on top of the i-th person
             */
            tower subtower = highest_tower_1(
                people_without_i, people[i].weight, people[i].height);

            /* if we found a new highest tower, update 'highest' */
            if (subtower.size() + 1 > highest.size())
            {
                highest = subtower;
                highest.push_front(people[i]);
            }
        }
    }

    return highest;
}

/**
 * @brief Comparison function which orders an array of people by height and, for
 *        each group of people having the same height, orders them by weight.
 * @note Complexity: O(1) in both time and space.
 */
bool person_compare(const person& p1, const person& p2)
{
    if (p1.height != p2.height)
    {
        return (p1.height < p2.height);
    }

    return (p1.weight < p2.weight);
}

/**
 * @brief Determines the highest tower which can be formed for a group of people
 *        using dynamic programming.
 * @note Complexity: O(n²), where n is the total number of people available.
 */
tower highest_tower_2(group people)
{
    if (people.empty() == true)
    {
        return {};
    }

    constexpr size_t NOBODY = std::numeric_limits<size_t>::max();

    /*
     * order people by height first and weight second; the resulting
     * array of people will be such that person i' > i cannot be on
     * top of i, so every person which can possibly be on top of i must
     * be to its left
     */
    std::sort(people.begin(), people.end(), person_compare);

    /*
     * highest_from[i] will store the highest possible tower if the i-th
     * person is at the tower base
     */
    std::vector<size_t> highest_from(people.size());

    /*
     * person_above[i] will store the person right above the i-th person
     * on the highest tower which can be formed with i as base
     */
    std::vector<size_t> person_above(people.size(), NOBODY);

    for (size_t i = 0; i < people.size(); ++i)
    {
        highest_from[i] = 1;

        /*
         * try to put all valid and previously formed towers with base
         * person j < i on top of i; keep only the highest one
         */
        for (size_t j = 0; j < i; ++j)
        {
            if (people[j].weight < people[i].weight &&
                people[j].height < people[i].height &&
                highest_from[j] + 1 > highest_from[i])
            {
                highest_from[i] = highest_from[j] + 1;
                person_above[i] = j;
            }
        }
    }

    /* find the person k which is at the base of the highest possible tower */
    size_t k = 0;

    for (size_t i = 1; i < people.size(); ++i)
    {
        k = highest_from[i] > highest_from[k] ? i : k;
    }

    /* now form the highest possible tower */
    tower highest = {people[k]};

    /* look for the next person on the tower until we are done */
    while (person_above[k] != NOBODY)
    {
        highest.push_back(people[person_above[k]]);
        k = person_above[k];
    }

    return highest;
}

/**
 * @brief Returns true if the tower of people is valid, false otherwise.
 * @note Complexity: O(m) in time, O(1) in space, where m is the tower height.
 */
bool is_valid_solution(const tower& solution)
{
    for (size_t i = 1; i < solution.size(); ++i)
    {
        const person& above = solution[i];
        const person& below = solution[i - 1];

        if (above.weight >= below.weight || above.height >= below.height)
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Generates a random group of n people with heights in [100,200]cm and
 *        weights in [40,120]kg.
 * @note Complexity: O(n) in both time and space.
 */
group random_group(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> height_chooser(100, 200);
    std::uniform_int_distribution<int> weight_chooser(40, 120);

    group people;

    while (people.size() < n)
    {
        int height = height_chooser(generator);
        int weight = weight_chooser(generator);

        people.push_back({height, weight});
    }

    return people;
}

int main()
{
    for (size_t n = 0; n <= 20; ++n)
    {
        for (int i = 0; i < 100; ++i)
        {
            group people = random_group(n);

            tower highest_1 = highest_tower_1(people);
            tower highest_2 = highest_tower_2(people);

            assert(highest_1.size() == highest_2.size());

            assert(is_valid_solution(highest_1));
            assert(is_valid_solution(highest_2));
        }

        std::cout << "passed random tests for groups of size " << n
                  << std::endl;
    }
}
