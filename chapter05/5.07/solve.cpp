/*
 * TASK: You are given an array holding n unique 32-bit integer values in the
 *       range [0,n]. Since the array contains only n values, one of the values
 *       in [0,n] is missing. Determine this missing value assuming that you
 *       can only access values in the array one bit at a time, i.e., given
 *       i in [0,n) and j in [0,31], your only "read" operation is "read the
 *       j-th bit of the i-th array value".
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief A representation of an array of 32-bit integers such that we can only
 *        access a single bit of a given integer at a time, i.e., the j-th bit
 *        of the i-th integer for some j in [0,31].
 */
class binary_array
{
public:
    void push_back(const uint32_t x)
    {
        values.push_back(x);
    }

    bool get_bit(const uint32_t i, const uint32_t j) const
    {
        assert(j < 32);
        return values[i] & (1U << j);
    }

    uint32_t size() const
    {
        return values.size();
    }

private:
    std::vector<uint32_t> values;
};

/**
 * @brief Finds the integer value missing on a binary array containing n unique
 *        values in [0,n] using xor operations.
 * @note Complexity: O(n) in time, O(1) in space.
 */
uint32_t find_missing_integer_1(const binary_array& v)
{
    uint32_t missing = 0;

    /*
     * set missing to the result of xoring every single integer value on
     * v; compute the xor operations bit by bit
     */
    for (uint32_t j = 0; j < 32; ++j)
    {
        bool bit = false;

        for (uint32_t i = 0; i < v.size(); ++i)
        {
            bit ^= v.get_bit(i, j);
        }

        missing |= bit << j;
    }

    /*
     * now xor missing with all values in [0,n]; the result will be the
     * single missing integer in this range
     */
    for (uint32_t x = 0; x < v.size() + 1; ++x)
    {
        missing ^= x;
    }

    return missing;
}

/**
 * @brief Finds the integer value missing on a binary array containing n unique
 *        values in [0,n] by manually building these values bit by bit and then
 *        marking the ones seen.
 * @note Complexity: O(n) in both time and space.
 */
uint32_t find_missing_integer_2(const binary_array& v)
{
    std::vector<bool> seen(v.size() + 1, false);

    /*
     * build the integer values in v one by one and then mark the ones
     * which are seen
     */
    for (uint32_t i = 0; i < v.size(); ++i)
    {
        uint32_t x = 0;

        for (uint32_t j = 0; j < 32; ++j)
        {
            x |= v.get_bit(i, j) << j;
        }

        seen[x] = true;
    }

    /* now go through 'seen' to figure out which value is missing */
    for (uint32_t x = 0; x < v.size() + 1; ++x)
    {
        if (seen[x] == false)
        {
            return x;
        }
    }

    throw std::logic_error("no value missing");
}

/**
 * @brief Returns a random vector containing n unique integer values in [0,n],
 *        with the single missing value from [0,n] being chosen randomly.
 * @note Complexity: O(n) in both time and space.
 */
binary_array random_vector(const uint32_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<uint32_t> distribution(0, n);

    /* select the missing value */
    uint32_t missing = distribution(generator);

    std::vector<uint32_t> values;

    for (uint32_t x = 0; x <= n; ++x)
    {
        if (x != missing)
        {
            values.push_back(x);
        }
    }

    std::shuffle(values.begin(), values.end(), generator);

    binary_array v;

    for (const uint32_t x : values)
    {
        v.push_back(x);
    }

    return v;
}

int main()
{
    for (uint32_t n = 1; n <= 100; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            binary_array v = random_vector(n);

            assert(find_missing_integer_1(v) == find_missing_integer_2(v));
        }

        std::cout << "passed random tests for arrays of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
