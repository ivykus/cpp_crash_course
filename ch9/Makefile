CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++20
all: 9-0 9-1 9-2 9-3

9-0: 9-0.cpp
	$(CXX) $(CXXFLAGS) -o 9-0 9-0.cpp 
	./9-0

9-1: 9-1.cpp
	$(CXX) $(CXXFLAGS) -o 9-1 9-1.cpp 
	./9-1

9-2: 9-2.cpp
	$(CXX) $(CXXFLAGS) -o 9-2 9-2.cpp 
	./9-2

9-3: 9-3.cpp
	$(CXX) $(CXXFLAGS) -o 9-3 9-3.cpp 
	./9-3

.PHONY: clean 9-0 9-1 9-2 9-3

clean:
	rm -f 9-0 9-1 9-2 9-3