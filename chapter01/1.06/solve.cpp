/*
 * TASK: You are given an image whose pixels (4 bytes each) are stored as an
 *       N×N matrix. Rotate the image by 90 degrees counterclockwise. Try to
 *       solve this problem in place (i.e., without generating a copy of the
 *       matrix).
 */

#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

class square_matrix
{
public:
    square_matrix(const size_t n) : n_(n), values_(n * n)
    {
        /* nothing needs to be done here */
    }

    int& operator()(const size_t i, const size_t j)
    {
        assert(i < n_ && j < n_);
        return values_[n_ * i + j];
    }

    int operator()(const size_t i, const size_t j) const
    {
        assert(i < n_ && j < n_);
        return values_[n_ * i + j];
    }

    size_t size() const
    {
        return n_;
    }

    bool operator==(const square_matrix& B) const
    {
        return values_ == B.values_;
    }

    std::ostream& print(std::ostream& stream = std::cout) const
    {
        for (size_t i = 0; i < n_; ++i)
        {
            for (size_t j = 0; j < n_; ++j)
            {
                stream << std::setw(5) << (*this)(i, j);
            }
            stream << std::endl;
        }

        return stream;
    }

private:
    size_t n_ = 0;
    std::vector<int> values_;
};

/**
 * @brief Solution which requires the matrix to be copied.
 * @return A copy of the input matrix rotated 90 degrees counterclockwise.
 * @note Complexity: O(n²) in time, O(n²) in space, where n is the matrix size.
 */
square_matrix rotate_square_matrix_1(const square_matrix& A)
{
    size_t n = A.size();

    square_matrix A_rot(n);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            /* (i,j) --> (n-1-j,i) */
            A_rot(n - 1 - j, i) = A(i, j);
        }
    }

    return A_rot;
}

/**
 * @brief Solution which rotates the matrix in place.
 * @return A reference to the input matrix (rotated 90 degrees
 *         counterclockwise).
 * @note Complexity: O(n²) in time, O(1) in space, where n is the matrix size.
 */
square_matrix& rotate_square_matrix_2(square_matrix& A)
{
    size_t n = A.size();

    for (size_t i = 0; i < n / 2; ++i)
    {
        for (size_t j = i; j < n - 1 - i; ++j)
        {
            /* (i,j) --> (n-1-j,i) */
            int a1 = A(n - 1 - j, i);
            A(n - 1 - j, i) = A(i, j);

            /* (n-1-j,i) --> (n-1-i,n-1-j) */
            int a2 = A(n - 1 - i, n - 1 - j);
            A(n - 1 - i, n - 1 - j) = a1;

            /* (n-1-i,n-1-j) --> (j,n-1-i) */
            int a3 = A(j, n - 1 - i);
            A(j, n - 1 - i) = a2;

            /* (j,n-1-i) --> (i,j) */
            A(i, j) = a3;
        }
    }

    return A;
}

/**
 * @brief Generates a random n×n matrix.
 * @note Complexity: O(n²) in both time and space.
 */
square_matrix random_matrix(const size_t n)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> distribution(0, 1000);

    square_matrix A(n);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            A(i, j) = distribution(generator);
        }
    }

    return A;
}

int main()
{
    for (size_t n = 0; n <= 50; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            square_matrix A = random_matrix(n);

            square_matrix A_rot = rotate_square_matrix_1(A);
            rotate_square_matrix_2(A);

            assert(A == A_rot);
        }

        std::cout << "passed random tests for matrices of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
