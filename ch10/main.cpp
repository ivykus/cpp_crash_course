#include "autobrake.h"
#include <iostream>
#include <stdexcept>


struct MockServiceBus : IServiceBus {
  void publish(const BrakeCommand &cmd) override {
    commands_published++;
    last_command = cmd;
  }
  void subscribe(SpeedUpdateCallback cb) override {
    speed_update_callback = cb;
  }
  void subscribe(CarDetectedCallback cb) override {
    car_detected_callback = cb;
  }
  BrakeCommand last_command{};
  int commands_published{};
  SpeedUpdateCallback speed_update_callback{};
  CarDetectedCallback car_detected_callback{};
};

constexpr void assert_that(bool statement, const char *msg) {
  if (!statement)
    throw std::runtime_error{msg};
}

void initial_speed_is_zero() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
  assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal to 0");
}

void initial_sensitivity_is_five() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
  assert_that(auto_brake.get_collision_threshold_s() == 5L,
              "sensitivity not equal to 5");
}

void sencitivity_greater_than_1() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
  try {
    auto_brake.set_collision_threshold_s(0.5L);
  } catch (const std::exception &) {
    return;
  }

  assert_that(false, "no exception thrown");
}

void speed_is_saved() {
  MockServiceBus bus{};
  AutoBrake ab{bus};
  bus.speed_update_callback(SpeedUpdate{100L});
  assert_that(100L == ab.get_speed_mps(), "speed not saved to 100");
  bus.speed_update_callback(SpeedUpdate{50L});
  assert_that(50L == ab.get_speed_mps(), "speed not saved to 50");
  bus.speed_update_callback(SpeedUpdate{0L});
  assert_that(0L == ab.get_speed_mps(), "speed not saved to 0");
}

void alert_when_imminent() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
  auto_brake.set_collision_threshold_s(10L);
  bus.speed_update_callback(SpeedUpdate{100L});
  bus.car_detected_callback(CarDetected{100L, 0L});
  assert_that(bus.commands_published == 1, "brake commands published not 1");
  assert_that(bus.last_command.time_to_collision_s == 1L,
              "time to collision not 1");
}

void no_alert_when_not_imminent() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};

  auto_brake.set_collision_threshold_s(2L);
  bus.speed_update_callback(SpeedUpdate{100L});
  bus.car_detected_callback(CarDetected{1000L, 50L});
  assert_that(bus.commands_published == 0, "brake command published");
}

void run_test(void (*unit_test)(), const char *name) {
  try {
    unit_test();
    std::cout << "[+] Test " << name << " successful.\n";
  } catch (const std::exception &e) {
    std::cout << "[-] Test failure in " << name << ". " << e.what() << '\n';
  }
}

int main() {
  run_test(initial_speed_is_zero, "initial speed is 0");
  run_test(initial_sensitivity_is_five, "initial sencitivity is 5");
  run_test(sencitivity_greater_than_1, "sencitivity greater than 1");
  run_test(speed_is_saved, "speed is saved");
  run_test(alert_when_imminent, "alert when imminent");
  run_test(no_alert_when_not_imminent, "no alert when not imminent");
}