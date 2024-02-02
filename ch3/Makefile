CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20

all: 3-2 3-3 3-4

3-2: 3-3.cpp
	$(CXX) $(CXXFLAGS) 3-2.cpp -o 3-2
	./3-2

3-3: 3-3.cpp
	$(CXX) $(CXXFLAGS) 3-3.cpp -o 3-3
	./3-3

3-4: 3-4.cpp
	$(CXX) $(CXXFLAGS) 3-4.cpp -o 3-4
	./3-4

.PHONY: clean 3-2 3-3 3-4
clean:
	rm -f 3-2 3-3 3-4