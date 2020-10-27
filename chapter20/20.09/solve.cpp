/*
 * TASK: Given a finite sequence of numbers x_i for i = 1, 2, ..., N, determine
 *       the medians of all partial sequences { x_1, ..., x_n } for all n in
 *       [1,N]. Your solution should not depend on N, i.e., it should work for
 *       sequences of arbitrary and unspecified sizes.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

/**
 * @brief A class which processes one value in the sequence at a time; since it
 *        stores all values read, it will require O(n) space by the time the
 *        n-th sequence value is processed.
 */
class sequence_median
{
public:
    /**
     * @brief Stores a new sequence value internally.
     * @note Complexity: O(log(n)) in time, O(1) in space, where n is the
     *       number of values added so far.
     */
    void push(const double x)
    {
        /* the first sequence value is always added to low */
        if (low.empty() == true || x <= low.top())
        {
            low.push(x);
        }
        else /* x > low.top() */
        {
            high.push(-x);
        }

        /*
         * make sure the difference in size between the low and high
         * heaps never exceeds one
         */
        if (low.size() + 1 < high.size())
        {
            low.push(-high.top());
            high.pop();

            assert(low.size() == high.size());
        }
        else if (high.size() + 1 < low.size())
        {
            high.push(-low.top());
            low.pop();

            assert(high.size() == low.size());
        }
    }

    /**
     * @brief Returns the median of the values already processed.
     * @note Complexity: O(1) in both time and space.
     */
    double median() const
    {
        if (low.size() == high.size())
        {
            return (low.top() - high.top()) / 2.0;
        }
        else if (low.size() > high.size())
        {
            return low.top();
        }
        else /* low.size() < high.size() */
        {
            return -high.top();
        }
    }

private:
    std::priority_queue<double> low;
    std::priority_queue<double> high;
};

/**
 * @brief Computes the median of a vector v by sorting its values first.
 * @note Complexity: O(n*log(n)) in time, O(n) in space.
 */
double median(std::vector<double> v)
{
    std::sort(v.begin(), v.end());

    const size_t n = v.size();

    if (n % 2 == 0)
    {
        return (v[(n - 1) / 2] + v[n / 2]) / 2.0;
    }
    else
    {
        return v[n / 2];
    }
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    sequence_median M;
    std::vector<double> v;

    for (int i = 0; i < 1000; ++i)
    {
        double x = distribution(generator);

        M.push(x);
        v.push_back(x);

        assert(M.median() == median(v));
    }

    std::cout << "passed random test" << std::endl;

    return EXIT_SUCCESS;
}
