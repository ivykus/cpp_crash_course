// Implement a PrimeNumberRange class that can be used in a range exception
// to iterate over all prime numbers less than a given value. Again, use a separate
// header and source file.

#include "prim.h"

#include <iostream>

int main() {
    for (auto n : PrimeNumberRange{5000}) {
        std::cout << n << '\n';
    }
}