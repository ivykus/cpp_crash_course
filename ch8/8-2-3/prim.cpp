#include "prim.h"

#include <stdexcept>

PrimeIterator PrimeNumberRange::begin() const { return PrimeIterator{max}; }

int PrimeNumberRange::end() const { return max; }

int PrimeIterator::operator*() const { return cur; }

PrimeIterator &PrimeIterator::operator++() {
  cur += 1;
  while (cur < sieve_sz) {
    if (!sieve[cur])
      return *this;
    cur++;
  }
  throw std::out_of_range("PrimeIterator out of range");
}

bool PrimeIterator::operator!=(int x) const { return cur < x; }

void PrimeIterator::fillSieve() {
  sieve[0] = 1;
  sieve[1] = 1;

  for (int i = 2; i < sieve_sz; i++) {
    if (sieve[i] == 0) {
      for (int j = i + i; j < sieve_sz; j += i) {
        sieve[j] = 1;
      }
    }
  }
}

PrimeIterator::PrimeIterator(int max) {
  if (max < 2 || max >= sieve_sz) {
    throw std::out_of_range("wrong range for PrimeIterator");
  }
  fillSieve();
}