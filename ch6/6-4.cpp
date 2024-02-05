#include <concepts>
#include <cstddef>
#include <iostream>

// Refactor mean in Listing 6-13 to accept an array rather than pointer and
// length arguments. Use Listing 6-33 as a guide.

template <typename T>
concept Averagable =
    std::default_initializable<T> && requires(T a, T b, size_t size) {
      { a += b } -> std::same_as<T &>;
      { a / size } -> std::convertible_to<T>;
    };

template <Averagable T, size_t Length> T mean(T(&a)[Length]) {
  T sum{};
  for (size_t i = 0; i < Length; ++i) {
    sum += a[i];
  }
  return sum / Length;
}

int main() {
    int x[]{1, 1, 1, -10, 1, 3, 4, 7, 8, 8, 8, 8};

    auto m = mean<int, sizeof(x) / sizeof(x[0])>(x);
    std::cout << m << std::endl;
}