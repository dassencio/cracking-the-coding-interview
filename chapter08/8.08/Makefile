CXXFLAGS := -g -std=c++11 -Wall -Wextra -Werror

# suppress an incorrect warning from clang
ifeq ($(CXX),clang++)
	CXXFLAGS += -Wno-missing-braces
endif

all: solve

solve: solve.cpp
	$(CXX) $(CXXFLAGS) solve.cpp -o solve

test: solve
	./solve

clean:
	rm -f solve
