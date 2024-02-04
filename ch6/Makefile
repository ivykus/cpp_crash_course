CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20

all: 6-0 6-1 6-2-3 6-4

6-0: 6-0.cpp
	$(CXX) $(CXXFLAGS) 6-0.cpp -o 6-0
	./6-0

6-1: 6-1.cpp
	$(CXX) $(CXXFLAGS) 6-1.cpp -o 6-1
	./6-1
6-2-3: 6-2-3.cpp
	$(CXX) $(CXXFLAGS) 6-2-3.cpp -o 6-2-3
	./6-2-3
6-4: 6-4.cpp
	$(CXX) $(CXXFLAGS) 6-4.cpp -o 6-4
	./6-4

.PHONY: clean 6-0 6-1 6-2-3 6-4
clean:
	rm -f 6-0 6-1 6-2-3 6-4