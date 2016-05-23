/*
 * TASK: You are given an M×N matrix. For each element M(i,j) which is zero,
 *       make all elements in the i-th row and the j-th column equal to zero.
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include <random>	/* std::uniform_int_distribution */
#include <cassert>

/* a simple matrix class */
class matrix
{
public:
	matrix(const size_t m, const size_t n): m_(m), n_(n), values_(m*n)
	{
		/* nothing needs to be done here */
	}

	int& operator()(const size_t i, const size_t j)
	{
		assert(i < m_ && j < n_);
		return values_[n_*i + j];
	}

	int operator()(const size_t i, const size_t j) const
	{
		assert(i < m_ && j < n_);
		return values_[n_*i + j];
	}

	size_t num_rows() const
	{
		return m_;
	}

	size_t num_cols() const
	{
		return n_;
	}

	bool operator==(const matrix& B) const
	{
		return (m_ == B.m_) && (values_ == B.values_);
	}

	std::ostream& print(std::ostream& stream = std::cout) const
	{
		for (size_t i = 0; i < m_; ++i)
		{
			for (size_t j = 0; j < n_; ++j)
			{
				stream << std::setw(5) << (*this)(i,j);
			}
			stream << std::endl;
		}

		return stream;
	}

private:
	size_t m_ = 0;
	size_t n_ = 0;
	std::vector< int > values_;
};

/**
 * @brief solution which requires the matrix to be copied
 * @return copy of input matrix with relevant rows/columns zeroed out
 * @note complexity: O(m*n) in both time and space
 */
matrix zero_when_necessary_1(const matrix& A)
{
	size_t m = A.num_rows();
	size_t n = A.num_cols();

	matrix A_zero = A;

	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (A(i,j) == 0)
			{
				/* zero-out the i-th row */
				for (size_t k = 0; k < n; ++k)
				{
					A_zero(i,k) = 0;
				}
				/* zero-out the j-th column */
				for (size_t k = 0; k < m; ++k)
				{
					A_zero(k,j) = 0;
				}
			}
		}
	}

	return A_zero;
}

/**
 * @brief solution which zoeres the relevant rows/columns in place
 * @return reference to input matrix (with rows/columns zeroed out)
 * @note complexity: O(m*n) in time, O(m+n) in space
 */
matrix zero_when_necessary_2(matrix& A)
{
	size_t m = A.num_rows();
	size_t n = A.num_cols();

	std::vector< bool > row_has_zero(m, false);
	std::vector< bool > col_has_zero(n, false);

	/* step 1: find out which rows/columns have zeros */
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (A(i,j) == 0)
			{
				row_has_zero[i] = true;
				col_has_zero[j] = true;
			}
		}
	}

	/* step 2: zero out the rows/columns which have zeros */
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (row_has_zero[i] || col_has_zero[j])
			{
				A(i,j) = 0;
			}
		}
	}

	return A;
}

/**
 * @brief generates a random m×n matrix
 * @note complexity: O(m*n) in both time and space
 */
matrix random_matrix(const size_t m, const size_t n)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	std::uniform_int_distribution< int > distribution(0,100);

	matrix A(m,n);

	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			A(i,j) = distribution(generator);
		}
	}

	return A;
}

int main()
{
	for (size_t m = 0; m <= 20; ++m)
	{
		for (size_t n = 0; n <= 20; ++n)
		{
			for (int i = 0; i < 1000; ++i)
			{
				matrix A = random_matrix(m,n);

				matrix A_zero = zero_when_necessary_1(A);
				zero_when_necessary_2(A);

				assert(A == A_zero);
			}
			std::cout << "passed random tests for matrices of size "
				  << m << "×" << n << std::endl;
		}
	}

	return 0;
}
