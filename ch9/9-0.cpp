#include <iostream>
#include <cstdint>

template <typename T>
constexpr T sum(T a) {
    return a; 
}

template <typename T, typename ...Args>
constexpr auto sum(T a, Args ...args) {
    return a + sum(args...);
}

template <typename... T>
constexpr auto sum2(T... args) {
    return (args + ...);
}

class CountIf {
    private:
    char ch;
    public:
    CountIf(char c) : ch(c) {}
    int operator()(const char *str) {
        int index{0};
        int result{0};
        while(str[index]) {
            if(str[index] == ch) {
                result++;
            }
            index++;
        }
        return result;
    }
};

int main() {
    #if 0
    std::cout << sum(1, 2, 4, 9, 12) << std::endl;
    std::cout << sum2(1, 2, 4, 9, 12) << std::endl;
    #endif

    CountIf ca{'a'};
    std::cout << ca("abra cadabra") << std::endl;
}