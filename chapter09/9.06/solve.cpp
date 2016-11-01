/*
 * TASK: You are given a matrix A such that for any given row and column, the
 *       elements on that row/column are sorted in ascending order, i.e., for
 *       a given pair of indices (i,j), A(i',j) <= A(i,j) for all i' < i and
 *       A(i,j') <= A(i,j) for all j' < j. For a given value x, find it in the
 *       matrix.
 */

#include <vector>
#include <utility>
#include <iostream>
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

private:
	size_t m_;
	size_t n_;
	std::vector< int > values_;
};

/**
 * @brief returns the position (i,j) of a value x on an m×n matrix A or (m,n) if
 *        x could not be found in A
 * @note complexity: O(m+n) in time, O(1) in space
 */
std::pair< size_t, size_t > find(const matrix& A, const int x)
{
	size_t m = A.num_rows();
	size_t n = A.num_cols();

	if (m == 0 || n == 0)
	{
		return {m,n};
	}

	/* start on the rightmost column, first row of A */
	size_t j = n - 1;
	size_t i = 0;

	/*
	 * invariant: all columns j' > j (i.e., to the right of j) and all rows
	 * i' < i (i.e., above i) have been eliminated
	 */
	while (true)
	{
		if (A(i,j) == x)
		{
			return {i,j};
		}
		/*
		 * if A(i,j) > x, all values A(i',j) for i' >= i are larger
		 * than x since column values are sorted, so we can discard them
		 */
		else if (A(i,j) > x)
		{
			if (j == 0)
			{
				break;
			}

			--j;
		}
		/*
		 * if A(i,j) < x, all values A(i,j') for j' <= j are smaller
		 * than x since row values are sorted, so we can discard them
		 */
		else /* A(i,j) < x */
		{
			++i;

			if (i == m)
			{
				break;
			}
		}
	}

	return {m,n};
}

int main()
{
	for (size_t m = 0; m <= 10; ++m)
	{
		for (size_t n = 0; n <= 10; ++n)
		{
			matrix A(m,n);

			int current = 0;

			for (size_t i = 0; i < m; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					A(i,j) = current;
					++current;
				}
			}

			for (int x = -current; x <= 2*current; ++x)
			{
				auto p = find(A,x);

				if (x < 0 || x >= current)
				{
					assert(p.first == m && p.second == n);
				}
				else
				{
					assert(A(p.first,p.second) == x);
				}
			}

			std::cout << "passed test for matrix of size " << m << "×" << n << std::endl;
		}
	}

	return 0;
}
