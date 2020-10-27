CXXFLAGS := -g -std=c++11 -Wall -Wextra -Werror -Wno-self-assign

all: solve

solve: solve.cpp
	$(CXX) $(CXXFLAGS) solve.cpp -o solve

test: solve
	./solve

clean:
	rm -f solve
