![Functional tests](https://github.com/dassencio/cracking-the-coding-interview/workflows/Functional%20tests/badge.svg)

# Description

Solutions (in C++) to selected problems from the book "Cracking the Coding
Interview, 4th Edition - 150 Programming Interview Questions and Solutions".

# License

All code from this project is licensed under the GPLv3. See the
[`LICENSE`](https://github.com/dassencio/cracking-the-coding-interview/tree/master/LICENSE)
file for more information.

# Usage instructions

Each solution in this repository is self-contained. Each directory contains
the solution to a given problem and tests to check its correctness (most of the
tests are randomized). To run the tests for a given problem, enter its
associated directory and run:

    make test

For the majority of the problems, this will simply generate and run an
executable file called `solve` which tests the provided solution.
Problems `13.01`, `19.08`, `20.10` and `20.13` require user input to be tested
and are therefore accompanied by Bash scripts called `run-tests` which generate
the necessary input for testing them. See the comments on top of the associated
`main()` functions for these problems for instructions on how to test their
solutions manually.

# Contributors & contact information

Diego Assencio / diego@assencio.com
