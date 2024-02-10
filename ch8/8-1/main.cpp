#include "fib.h"
#include <iostream>


int main() {
    for (const auto& x: FibonacciRange(500)) {
        std::cout << x << std::endl;
    }
}