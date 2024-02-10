#ifndef PRIMGENN_H
#define PRIMGENN_H

class PrimeIterator {
private:
  const static int sieve_sz{10000};
  int sieve[sieve_sz]{};
  int cur{2};

  int getMax() const;
  void fillSieve();

public:
  PrimeIterator(int max);
  int operator*() const;
  PrimeIterator &operator++();
  bool operator!=(int x) const;
};
class PrimeNumberRange {

public:
  PrimeNumberRange(int max) : max(max) {}
  PrimeIterator begin() const;
  int end() const;

private:
  int max;
};
#endif