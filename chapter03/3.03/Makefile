CXXFLAGS := -g -std=c++11 -Wall -Wextra -Werror

all: solve

solve: solve.cpp stacks.hpp
	$(CXX) $(CXXFLAGS) solve.cpp -o solve

test: solve
	./solve

clean:
	rm -f solve
