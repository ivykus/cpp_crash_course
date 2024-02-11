// 9-3. Implement an all function with the following prototype:
// template <typename Fn, typename In, typename Out>
// constexpr bool all(Fn function, In* input, size_t length);
// The Fn function type is a predicate that supports bool operator()(In).
// Your all function must test whether function returns true for every element
// of input. If it does, return true. Otherwise, return false. For example, your
// implementation must support the following usage: int main() {
//   int data[]{ 100, 200, 300, 400, 500 };
//   size_t data_len = 5;
//   auto all_gt100 = all([](auto x) { return x > 100; }, data, data_len);
//   if(all_gt100) printf("All elements greater than 100.\n");
// }
#include <cstddef>
#include <iostream>

template <typename Fn, typename In>
constexpr bool all(Fn function, In *input, size_t length) {
  bool result = true;
  for (size_t i = 0; i < length; i++) {
    if (!function(input[i])) {
      result = false;
      break;
    }
  }
  return result;
}

int main() {
  int data[]{100, 200, 300, 400, 500, 100, 800};
  size_t data_len = 7;
  auto all_gt100 = all([](auto x) { return x > 100; }, data, data_len);
  if (all_gt100) {
    std::cout << "All elements greater than 100." << std::endl;
  } else {
    std::cout << "Not all elements greater than 100." << std::endl;
  }
}
