#include "fib.h"
#include <iostream>

// 8-1. Refactor Listing 8-27 into separate translation units: one for main and
// another for FibonacciRange and FibonacciIterator. Use a header file to share
// definitions between the two translation units.

int main() {
    for (const auto& x: FibonacciRange(500)) {
        std::cout << x << std::endl;
    }
}