/*
 * TASK: Given an n×n matrix M of integer values (which can be positive or
 *       negative), determine its largest-sum submatrix, i.e., the submatrix of
 *       M whose element sum is the largest among all submatrices of M.
 */

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/* a simple matrix class */
class matrix
{
public:
    matrix(const size_t m = 0, const size_t n = 0)
        : m_(m), n_(n), values_(m * n)
    {
        /* nothing needs to be done here */
    }

    int& operator()(const size_t i, const size_t j)
    {
        assert(i < m_ && j < n_);
        return values_[n_ * i + j];
    }

    int operator()(const size_t i, const size_t j) const
    {
        assert(i < m_ && j < n_);
        return values_[n_ * i + j];
    }

    size_t num_rows() const
    {
        return m_;
    }

    size_t num_cols() const
    {
        return n_;
    }

private:
    size_t m_;
    size_t n_;
    std::vector<int> values_;
};

/**
 * @brief Computes the sum of all elements in the submatrix M(i1:i2, j1:j2).
 * @note Complexity: O((i2-i1)*(j2-j1)) in time, O(1) in space.
 */
int matrix_sum(const matrix& M,
               const size_t i1,
               const size_t j1,
               const size_t i2,
               const size_t j2)
{
    int sum = 0;

    for (size_t i = i1; i <= i2; ++i)
    {
        for (size_t j = j1; j <= j2; ++j)
        {
            sum += M(i, j);
        }
    }

    return sum;
}

/**
 * @brief Computes the sum of all elements in an m×n matrix M.
 * @note Complexity: O(m*n) in time, O(1) in space.
 */
int matrix_sum(const matrix& M)
{
    if (M.num_rows() == 0 || M.num_cols() == 0)
    {
        return 0;
    }

    return matrix_sum(M, 0, 0, M.num_rows() - 1, M.num_cols() - 1);
}

/**
 * @brief Computes the largest-sum submatrix of an n×n matrix M using brute
 *        force.
 * @note Complexity: O(n²) in space, O(n^6) in time (but could be O(1) in space
 *       if we did not build the solution manually).
 */
matrix largest_sum_submatrix_1(const matrix& M)
{
    size_t n = M.num_rows();

    if (n == 0)
    {
        return {};
    }

    int largest_sum = std::numeric_limits<int>::min();

    size_t i1 = std::numeric_limits<size_t>::max();
    size_t j1 = std::numeric_limits<size_t>::max();
    size_t i2 = std::numeric_limits<size_t>::max();
    size_t j2 = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            /*
             * for all I in [0,i] and all J in [0,j], compute the
             * sum of the elements in the submatrix M(I:i,J:j); by
             * considering all values i,j in [0,n), we will determine
             * the largest-sum submatrix
             */
            for (size_t I = 0; I <= i; ++I)
            {
                for (size_t J = 0; J <= j; ++J)
                {
                    int sum = matrix_sum(M, I, J, i, j);

                    if (sum > largest_sum)
                    {
                        i1 = I;
                        j1 = J;
                        i2 = i;
                        j2 = j;

                        largest_sum = sum;
                    }
                }
            }
        }
    }

    assert(i1 <= i2 && j1 <= j2);

    /* build the obtained largest-sum submatrix */
    matrix result(i2 - i1 + 1, j2 - j1 + 1);

    for (size_t i = i1; i <= i2; ++i)
    {
        for (size_t j = j1; j <= j2; ++j)
        {
            result(i - i1, j - j1) = M(i, j);
        }
    }

    return result;
}

/**
 * @brief Computes the largest-sum submatrix of an n×n matrix M using dynamic
 *        programming.
 * @note Complexity: O(n²) in space, O(n^4) in time (but could be O(1) in space
 *       if we did not build the solution manually).
 */
matrix largest_sum_submatrix_2(const matrix& M)
{
    size_t n = M.num_rows();

    if (n == 0)
    {
        return {};
    }

    int largest_sum = std::numeric_limits<int>::min();

    size_t i1 = std::numeric_limits<size_t>::max();
    size_t j1 = std::numeric_limits<size_t>::max();
    size_t i2 = std::numeric_limits<size_t>::max();
    size_t j2 = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            /* sum_submatrix(I,J) = sum(M(I:i,J:j)) */
            matrix sum_submatrix(i + 1, j + 1);

            /* sum_subcolumn(I,J) = sum(M(I:i,J)) */
            matrix sum_subcolumn(i + 1, j + 1);

            /*
             * for all I in [0,i] and all J in [0,j], compute the
             * sum of the elements in the submatrix M(I:i,J:j); by
             * considering all values i,j in [0,n), we will determine
             * the largest-sum submatrix (we compute the sum of the
             * elements in M(I:i,J:j) by adding the sum of all
             * elements in the submatrix M(I:i,J+1:j) and the sum of
             * all elements in the column submatrix M(I+1:i,J)
             */
            for (size_t di = 0; di <= i; ++di)
            {
                for (size_t dj = 0; dj <= j; ++dj)
                {
                    size_t I = i - di;
                    size_t J = j - dj;

                    sum_subcolumn(I, J) = M(I, J);

                    if (I < i)
                    {
                        sum_subcolumn(I, J) += sum_subcolumn(I + 1, J);
                    }

                    sum_submatrix(I, J) = sum_subcolumn(I, J);

                    if (J < j)
                    {
                        sum_submatrix(I, J) += sum_submatrix(I, J + 1);
                    }

                    if (sum_submatrix(I, J) > largest_sum)
                    {
                        i1 = I;
                        j1 = J;
                        i2 = i;
                        j2 = j;

                        largest_sum = sum_submatrix(I, J);
                    }
                }
            }
        }
    }

    assert(i1 <= i2 && j1 <= j2);

    /* build the obtained largest-sum submatrix */
    matrix result(i2 - i1 + 1, j2 - j1 + 1);

    for (size_t i = i1; i <= i2; ++i)
    {
        for (size_t j = j1; j <= j2; ++j)
        {
            result(i - i1, j - j1) = M(i, j);
        }
    }

    return result;
}

/**
 * @brief Generates a random n×n matrix.
 * @note Complexity: O(n²) in both time and space.
 */
matrix random_matrix(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(-100, 100);

    matrix M(n, n);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            M(i, j) = distribution(generator);
        }
    }

    return M;
}

int main()
{
    for (size_t n = 0; n <= 20; ++n)
    {
        for (int i = 0; i < 10; ++i)
        {
            matrix M = random_matrix(n);

            matrix S1 = largest_sum_submatrix_1(M);
            matrix S2 = largest_sum_submatrix_2(M);

            assert(matrix_sum(S1) == matrix_sum(S2));
        }

        std::cout << "passed random tests for matrices of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
