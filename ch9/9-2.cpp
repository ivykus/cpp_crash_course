// 9-2. Implement a program that accepts an arbitrary number of command line
// arguments, counts the length in characters of each argument,
// and prints a histogram of the argument length distribution.
#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

class histogram {
private:
  std::unordered_map<int, int> mp;

public:
  void digest(const char *str) { mp[std::strlen(str)]++; }

  void print() {
    std::for_each(mp.begin(), mp.end(), [](auto &p) {
      std::cout << p.first << ": ";
      for (int i = 0; i < p.second; ++i) {
        std::cout << "*";
      }
      std::cout << std::endl;
    });
  }
};

int main(int argc, char *argv[]) {
  histogram hm;

  for (int i = 0; i < argc; i++) {
    hm.digest(argv[i]);
  }
  hm.print();
}
