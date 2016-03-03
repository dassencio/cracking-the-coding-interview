#include <stack>
#include <iostream>
#include <cassert>

/**
 * @brief solves the Hanoi problem recursively
 * @param A the origin rod containing disks which must be moved
 * @param B the helper rod
 * @param C the target rod to which n disks from A must be moved
 * @param n the number of disks from A which must be moved to C (this number
 *        may be smaller than the total number of disks in A)
 * @note complexity: O(2^n) in time since the work T(n) done to move n
 *       disks from A to C requires 2T(n-1) + O(1) steps, O(n) in space
 *       because the recursion will not go deeper than O(n) levels inside
 *       this function and the function itself requires O(1) space in memory
 * @note the correctness of this method is easily proved by induction
 */
void solve(std::stack< size_t >& A,
           std::stack< size_t >& B,
           std::stack< size_t >& C,
           const size_t n)
{
	/* trivial problem: A has no disks which must be moved */
	if (n == 0)
	{
		return;
	}

	/* base case: move a single disk from A to C */
	if (n == 1)
	{
		C.push(A.top());
		A.pop();

		return;
	}

	/*
	 * if A has n > 1 disks which must be moved to C, first move the top
	 * n-1 disks to B, then move n-th disk from A to C, then solve this
	 * new problem: move n-1 disks from B to C using A as helper
	 */

	/* first: move n-1 disks from A to B using C as helper */
	solve(A, C, B, n-1);

	/* then: move A's n-th disk to C */
	C.push(A.top());
	A.pop();

	/* finally: move the n-1 disks placed on B to C using A as helper */
	solve(B, A, C, n-1);
}

int main()
{
	for (size_t n = 0; n <= 20; ++n)
	{
		std::stack< size_t > A, B, C;

		/* add n disks to A (labeled 0..n-1 from top to bottom) */
		for (size_t i = 0; i < n; ++i)
		{
			A.push(n-i-1);
		}

		solve(A, B, C, A.size());

		/* make sure all disks from A were moved to C */
		assert(A.size() == 0);
		assert(B.size() == 0);
		assert(C.size() == n);

		/* make sure the order of the disks on C is valid */
		for (size_t i = 0; i < n; ++i)
		{
			assert(C.top() == i);
			C.pop();
		}

		std::cout << "passed test for tower of height " << n << std::endl;
	}

	return 0;
}
