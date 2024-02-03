#include <iostream>
#include <chrono>
#include <thread>

struct TimerClass {
    std::chrono::steady_clock::time_point timestamp;
    TimerClass() {
        timestamp = std::chrono::steady_clock::now();
    }

    TimerClass(const TimerClass &) = delete;
    
    TimerClass& operator=(const TimerClass &) = delete;

    TimerClass(TimerClass &&) = delete;
    
    TimerClass& operator=(TimerClass&&) = delete;
        
    ~TimerClass() {
        auto now = std::chrono::steady_clock::now();
        auto age = now - timestamp;
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(age).count() << std::endl;
    }
};

int main() {
    {
        TimerClass t1;
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }
    std::cout << "Done" << std::endl;
    
}