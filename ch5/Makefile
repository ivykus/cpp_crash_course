CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20

all: 5-0 5-1 5-2-3 5-4

5-0: 5-0.cpp
	$(CXX) $(CXXFLAGS) 5-0.cpp -o 5-0
	./5-0

5-1: 5-1.cpp
	$(CXX) $(CXXFLAGS) 5-1.cpp -o 5-1
	./5-1
5-2-3: 5-2-3.cpp
	$(CXX) $(CXXFLAGS) 5-2-3.cpp -o 5-2-3
	./5-2-3
5-4: 5-4.cpp
	$(CXX) $(CXXFLAGS) 5-4.cpp -o 5-4
	./5-4

.PHONY: clean 5-0 5-1 5-2-3 5-4
clean:
	rm -f 5-0 5-1 5-2-3 5-4