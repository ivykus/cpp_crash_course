#include <chrono>
#include <iostream>
#include <thread>

struct TimerClass {
private:
  bool is_moved = false;
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
  TimerClass(TimerClass &&other) noexcept {
    timestamp = other.timestamp;
    is_moved = true;
  }

  TimerClass &operator=(TimerClass &&other) noexcept {
    if (this != &other) {
      timestamp = other.timestamp;
      is_moved = true;
    }
    return *this;
  }

  ~TimerClass() {
    if (!is_moved) {
      auto now = std::chrono::steady_clock::now();
      auto age = now - timestamp;
      std::cout
          << std::chrono::duration_cast<std::chrono::milliseconds>(age).count()
          << std::endl;
    }
  }
};

int main() {

  {
    TimerClass t1;
    TimerClass t5;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    TimerClass t2(t1);
    TimerClass t3 = t1;
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    TimerClass t4(std::move(t1));
    TimerClass t6 = std::move(t5);
  }

  std::cout << "Done" << std::endl;
}