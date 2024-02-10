#ifndef FIBONACCI_H
#define FIBONACCI_H
class FibonacciIterator {
private:
  int prev{1};
  int cur{1};

public:
  int operator*() const;

  FibonacciIterator &operator++();
  bool operator!=(int x);
};

class FibonacciRange {
private:
  int max;

public:
  explicit FibonacciRange(int max) : max(max) {}

  FibonacciIterator begin() const;

  int end() const;
};

#endif
