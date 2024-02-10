CXX=clang++

CXXFLAGS=-Wall -Werror -std=c++20 -Wextra -Wpedantic

all : main

main : main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp prim.cpp
	./main

.PHONY : clean main

clean :
	rm -f main