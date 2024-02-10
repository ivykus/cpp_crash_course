#include "fib.h"

int FibonacciRange::end() const {
    return max;
}

FibonacciIterator FibonacciRange::begin() const {
    return FibonacciIterator{};
}

FibonacciIterator &FibonacciIterator::operator++() {
    int next = prev + cur;
    prev = cur;
    cur = next;
    return *this;
}

bool FibonacciIterator::operator!=(int x) {
    return x > cur;
}

int FibonacciIterator::operator*() const {
    return cur;
}