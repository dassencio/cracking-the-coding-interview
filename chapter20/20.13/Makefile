CXXFLAGS := -g -std=c++11 -Wall -Wextra -Werror -O3

all: solve

solve: solve.cpp
	$(CXX) $(CXXFLAGS) solve.cpp -o solve

test: solve
	./run-tests

clean:
	rm -f solve
