// 9-1. Implement a fold function template with the following prototype:
// template <typename Fn, typename In, typename Out>
// constexpr Out fold(Fn function, In* input, size_t length, Out initial);
// For example, your implementation must support the following usage:
// int main() {
// int data[]{ 100, 200, 300, 400, 500 };
// size_t data_len = 5;
// auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len,
// 0);
// print("Sum: %d\n", sum);
// }
// The value of sum should be 1,500. Use fold to calculate the following quanti-
// ties: the maximum, the minimum, and the number of elements greater than 200.

#include <iostream>
#include <cstddef>


template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
    for (size_t i = 0; i < length; i++) {
        initial = function(initial, input[i]);
    }
    return initial;
}

int main() {
    int data[]{100, 200, 300, 400, 500, 100, 800};
    size_t data_len = 7;
    auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
    auto max = fold([](auto x, auto y) { return x > y ? x : y; }, data, data_len, data[0]);
    auto min = fold([](auto x, auto y) { return x < y ? x : y; }, data, data_len, data[0]);
    auto greater = fold([](auto x, auto y) { return y > 200 ? x + 1 : x; }, data, data_len, 0);
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
    std::cout << "Greater than 200: " << greater << std::endl;
    return 0;
}