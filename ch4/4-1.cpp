#include <chrono>
#include <iostream>

struct TimerClass {
  std::chrono::steady_clock::time_point timestamp;

  TimerClass() { timestamp = std::chrono::steady_clock::now(); }
};

int main() {
  TimerClass t1;
  TimerClass t2;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                   t2.timestamp - t1.timestamp)
                   .count()
            << std::endl;
}