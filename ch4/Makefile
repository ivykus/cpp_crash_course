CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20

all: 4-1 4-2 4-3 4-4 4-5

4-1: 4-1.cpp
	$(CXX) $(CXXFLAGS) 4-1.cpp -o 4-1
	./4-1
4-2: 4-2.cpp
	$(CXX) $(CXXFLAGS) 4-2.cpp -o 4-2
	./4-2
4-3: 4-3.cpp
	$(CXX) $(CXXFLAGS) 4-3.cpp -o 4-3
	./4-3
4-4: 4-4.cpp
	$(CXX) $(CXXFLAGS) 4-4.cpp -o 4-4
	./4-4
4-5: 4-5.cpp
	$(CXX) $(CXXFLAGS) 4-5.cpp -o 4-5
	./4-5

.PHONY: clean 4-1 4-2 4-3 4-4 4-5
clean:
	rm -f 4-1 4-2 4-3 4-4 4-5