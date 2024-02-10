CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20
all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp fib.cpp
	./main

.PHONY: clean main

clean:
	rm -f main