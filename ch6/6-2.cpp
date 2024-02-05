#include <cstddef>
#include <iostream>

// Implement mode as a template function

// not checking for multiple modes
template <typename T> T any_mode(const T *values, size_t length) {
  if (!length)
    return 0;

  int count = 0;
  T candidate = values[0];
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
  auto m1 = any_mode(x, sizeof(x) / sizeof(x[0]));

  std::cout << m1 << std::endl;

  const float y[]{1, 2.4, 33, 2.8, 1};
  auto m2 = any_mode(y, sizeof(y) / sizeof(y[0]));
  std::cout << m2 << std::endl;
}