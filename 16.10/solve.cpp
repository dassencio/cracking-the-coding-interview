/*
 * TASK: Implement a function which allocates a two-dimensional array using as
 *       few calls to malloc as possible. Your two-dimensional array elements
 *       must be accessible as in array[i][j].
 */

#include <cstdlib>
#include <iostream>
#include <cassert>

/**
 * @brief returns an m×n matrix as a pointer to an array of pointers to elements
 * @note complexity: O(m*n) in both time and space
 * @note the structure of this matrix is as follows: we allocate space for all
 *       elements and for all pointers to the first element at each row; the
 *       row pointers are then written at the first m*sizeof(int*) bytes of
 *       the memory block, and the elements are written right after the pointer
 *       to the last row, with elements for each row being stored as contiguous
 *       sequences
 */
int** my_2d_alloc(const int m, const int n)
{
	/* number of bytes necessary to store a matrix row */
	int row_space = n*sizeof(int);

	/* memory layout: row pointers first, then the matrix elements */
	int** matrix = (int**)malloc(m*sizeof(int*) + m*row_space);

	/* set the row pointers */
	for (int i = 0; i < m; ++i)
	{
		matrix[i] = (int*)((char*)matrix + (m*sizeof(int*) + i*row_space));
	}

	return matrix;
}

int main()
{
	for (int m = 0; m < 10; ++m)
	{
		for (int n = 0; n < 10; ++n)
		{
			int** matrix = my_2d_alloc(m,n);

			for (int i = 0; i < m; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					matrix[i][j] = i*n + j;
				}
			}

			/* check if we corrupted anything */
			for (int i = 0; i < m; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					assert(matrix[i][j] == i*n + j);
				}
			}

			free(matrix);
		}
	}

	std::cout << "passed all tests" << std::endl;

	return 0;
}
