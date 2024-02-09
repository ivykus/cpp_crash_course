CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20

all: 7-0 7-1 7-2 7-3

7-0: 7-0.cpp
	$(CXX) $(CXXFLAGS) 7-0.cpp -o 7-0
	./7-0

7-1: 7-1.cpp
	$(CXX) $(CXXFLAGS) 7-1.cpp -o 7-1
	./7-1
7-2: 7-2.cpp
	$(CXX) $(CXXFLAGS) 7-2.cpp -o 7-2
	./7-2

.PHONY: clean 7-0 7-1 7-2
clean:
	rm -f 7-0 7-1 7-2