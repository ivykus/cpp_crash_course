#include "../autobrake.h"
#include <gtest/gtest.h>

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

struct AutoBrakeTest : ::testing::Test {
  MockServiceBus bus{};
  AutoBrake ab{bus}; 
};

TEST_F(AutoBrakeTest, InitialSpeedIsZero) {
  ASSERT_DOUBLE_EQ(0, ab.get_speed_mps());
}

TEST_F(AutoBrakeTest, InitialSensitivityIsFive) {
  ASSERT_DOUBLE_EQ(5, ab.get_collision_threshold_s());
}

TEST_F(AutoBrakeTest, SencitivityGreaterThanOne) {
  ASSERT_ANY_THROW(ab.set_collision_threshold_s(0.5));
}

TEST_F(AutoBrakeTest, SpeedIsSaved) {
  bus.speed_update_callback(SpeedUpdate{100});
  ASSERT_DOUBLE_EQ(100, ab.get_speed_mps());
  bus.speed_update_callback(SpeedUpdate{50});
  ASSERT_DOUBLE_EQ(50, ab.get_speed_mps());
  bus.speed_update_callback(SpeedUpdate{0});
  ASSERT_DOUBLE_EQ(0, ab.get_speed_mps());
}

TEST_F(AutoBrakeTest, NoAlertWhenNotImminent) {
  ab.set_collision_threshold_s(2L);
  bus.speed_update_callback(SpeedUpdate{100});
  bus.car_detected_callback(CarDetected{1000, 50});
  ASSERT_EQ(0, bus.commands_published);
}

TEST_F(AutoBrakeTest, AlertWhenImminent) {
  ab.set_collision_threshold_s(10L);
  bus.speed_update_callback(SpeedUpdate{100});
  bus.car_detected_callback(CarDetected{100, 0});
  ASSERT_EQ(1, bus.commands_published);
  ASSERT_DOUBLE_EQ(1, bus.last_command.time_to_collision_s);
}