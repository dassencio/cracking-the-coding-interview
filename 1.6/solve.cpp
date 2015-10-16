#include <vector>
#include <iostream>
#include <iomanip>
#include <random>	/* std::uniform_int_distribution */
#include <cassert>

/* a simple matrix class */
template< typename T >
class square_matrix
{
public:
	square_matrix(const size_t n): n_(n), values_(n*n)
	{
		/* nothing needs to be done here */
	}

	T& operator()(const size_t i, const size_t j)
	{
		assert(i < n_ && j < n_);
		return values_[n_*i + j];
	}

	const T& operator()(const size_t i, const size_t j) const
	{
		assert(i < n_ && j < n_);
		return values_[n_*i + j];
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
				stream << std::setw(5) << (*this)(i,j);
			}
			stream << std::endl;
		}

		return stream;
	}

private:
	size_t n_ = 0;
	std::vector< int > values_;
};

/**
 * @brief returns a rotated version of an input square matrix
 * @return copy of input matrix rotated 90 degrees counterclockwise
 * @note complexity: O(n²) in time, O(n²) in space
 */
template< typename T >
square_matrix< T > rotate_square_matrix_1(const square_matrix< T >& A)
{
	size_t n = A.size();

	square_matrix< T > A_rot(n);

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			/* (i,j) --> (n-1-j,i) */
			A_rot(n-1-j,i) = A(i,j);
		}
	}

	return A_rot;
}

/**
 * @brief rotates a square matrix in place
 * @return reference to input matrix (rotatetd 90 degrees counterclockwise)
 * @note complexity: O(n²) in time, O(1) in space
 */
template< typename T >
square_matrix< T >& rotate_square_matrix_2(square_matrix< T >& A)
{
	size_t n = A.size();

	for (size_t i = 0; i < n/2; ++i)
	{
		for (size_t j = i; j < n-1-i; ++j)
		{
			/* (i,j) --> (n-1-j,i) */
			T a1 = A(n-1-j,i);
			A(n-1-j,i) = A(i,j);

			/* (n-1-j,i) --> (n-1-i,n-1-j) */
			T a2 = A(n-1-i,n-1-j);
			A(n-1-i,n-1-j) = a1;

			/* (n-1-i,n-1-j) --> (j,n-1-i) */
			T a3 = A(j,n-1-i);
			A(j,n-1-i) = a2;

			/* (j,n-1-i) --> (i,j) */
			A(i,j) = a3;
		}
	}

	return A;
}

/**
 * @brief generates a random n×n matrix
 * @note complexity: O(n²) in both space and time
 */
square_matrix< int > random_matrix(const size_t n)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution< int > distribution(0,1000);

	square_matrix< int > A(n);

	for (size_t i = 0; i < n; ++i)
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
	for (size_t n = 0; n <= 50; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			square_matrix< int > A = random_matrix(n);

			square_matrix< int > A_rot = rotate_square_matrix_1(A);
			rotate_square_matrix_2(A);

			assert(A == A_rot);
		}
		std::cout << "passed random tests for matrices of size " << n << std::endl;
	}

	return 0;
}
