#include <cstddef>
#include <iostream>

// The mode of a series of values is the value that appears most commonly.
// Implement a mode function using the following signature: int mode(const
// int* values, size_t length). If you encounter an error condition, such as
// input having multiple modes and no values, return zero.

// not checking for multiple modes
int any_mode(const int *values, size_t length) {
  if (!length)
    return 0;

  int count = 0;
  int candidate = values[0];
  for (size_t i = 1; i < length; ++i) {
    if (values[i] != candidate) {
      if (count == 0) {
        candidate = values[i];
      } else {
        count--;
      }
    } else {
      count++;
    }
  }

  return candidate;
}

int main() {
  const int x[]{1, 1, 1, 1, 3, 4, 7, 8, 8, 8, 8};
  int m = any_mode(x, sizeof(x) / sizeof(x[0]));

  std::cout << m << std::endl;
}