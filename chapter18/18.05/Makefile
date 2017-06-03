CXXFLAGS := -g -std=c++11 -Wall -Wextra -Werror -pthread

all: solve

solve: solve.cpp
	$(CXX) $(CXXFLAGS) solve.cpp -o solve

test: solve
	./solve

clean:
	rm -f solve
