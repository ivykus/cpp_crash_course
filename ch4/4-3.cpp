#include <chrono>
#include <iostream>
#include <thread>

struct TimerClass {
private:
  std::chrono::steady_clock::time_point timestamp;

public:
  TimerClass() { timestamp = std::chrono::steady_clock::now(); }

  TimerClass(const TimerClass &other) { timestamp = other.timestamp; }

  TimerClass &operator=(const TimerClass &other) {
    if (this != &other) {
      timestamp = other.timestamp;
    }
    return *this;
  }

  TimerClass(TimerClass &&) = delete;
  TimerClass &operator=(TimerClass &&) = delete;
  ~TimerClass() {
    auto now = std::chrono::steady_clock::now();
    auto age = now - timestamp;
    std::cout
        << std::chrono::duration_cast<std::chrono::milliseconds>(age).count()
        << std::endl;
  }
};

int main() {
  {
    TimerClass t1;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    TimerClass t2(t1);
    TimerClass t3 = t1;
  }

  std::cout << "Done" << std::endl;
}