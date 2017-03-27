[![Build Status](https://travis-ci.org/dassencio/cracking-the-coding-interview.svg?branch=master)](https://travis-ci.org/dassencio/cracking-the-coding-interview)

Description
===========

Solutions (in C++) to selected problems from the book "Cracking the Coding
Interview, 4th Edition - 150 Programming Interview Questions and Solutions".


License
=======

All code from this project is licensed under the GPLv3. See the `LICENSE` file
for more information.


Usage instructions
==================

Each solution in this repository is self-contained. Each directory contains
the solution to a given problem and (except for solutions which require user
input) tests to check its correctness (most of the tests are randomized). To run
the tests for a given problem on Linux, enter the associated directory for that
solution and compile it first:

	make

The tests can then be executed by running:

	./solve

The solutions to problems `13.01`, `19.08`, `20.10` and `20.13` require user
input to be tested. See the comment right on top of their associated `main()`
functions for instructions on how to run them.


Contributors & contact information
==================================

Diego Assencio / diego@assencio.com
