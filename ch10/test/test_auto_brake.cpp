#include "../autobrake.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::A;
using ::testing::DoubleEq;
using ::testing::Field;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::StrictMock;

struct MockServiceBus : IServiceBus {
  MOCK_METHOD1(publish, void(const BrakeCommand &));
  MOCK_METHOD1(subscribe, void(SpeedUpdateCallback));
  MOCK_METHOD1(subscribe, void(CarDetectedCallback));
  MOCK_METHOD1(subscribe, void(SpeedLimitDetectedCallback));
};

struct NiceAutoBrakeTest : ::testing::Test {
  NiceMock<MockServiceBus> bus;
  AutoBrake auto_brake{bus};
};

struct StrictAutoBrakeTest : ::testing::Test {
  StrictAutoBrakeTest() {
    EXPECT_CALL(bus, subscribe(A<CarDetectedCallback>()))
        .Times(1)
        .WillOnce(Invoke([this](const auto &x) { car_detected_callback = x; }));
    EXPECT_CALL(bus, subscribe(A<SpeedUpdateCallback>()))
        .Times(1)
        .WillOnce(Invoke([this](const auto &x) { speed_update_callback = x; }));
    EXPECT_CALL(bus, subscribe(A<SpeedLimitDetectedCallback>()))
        .Times(1)
        .WillOnce(Invoke(
            [this](const auto &x) { speed_limit_detected_callback = x; }));
  }
  CarDetectedCallback car_detected_callback;
  SpeedUpdateCallback speed_update_callback;
  SpeedLimitDetectedCallback speed_limit_detected_callback;
  StrictMock<MockServiceBus> bus;
};

TEST_F(NiceAutoBrakeTest, initial_speed_is_zero) {
  ASSERT_DOUBLE_EQ(auto_brake.get_speed_mps(), 0L);
}

TEST_F(NiceAutoBrakeTest, Initial_speed_limit_mps_is_set) {
  ASSERT_EQ(Initial_speed_limit_mps, auto_brake.get_last_speed_limit_mps());
}

TEST_F(NiceAutoBrakeTest, InitialSensitivityIsFive) {
  ASSERT_DOUBLE_EQ(5, auto_brake.get_collision_threshold_s());
}

TEST_F(NiceAutoBrakeTest, SensitivityGreaterThanOne) {
  ASSERT_ANY_THROW(auto_brake.set_collision_threshold_s(0.5L));
}

TEST_F(StrictAutoBrakeTest, Speed_limits_are_saved) {
  AutoBrake auto_brake{bus};
  speed_limit_detected_callback(SpeedLimitDetected{100L});
  ASSERT_EQ(100L, auto_brake.get_last_speed_limit_mps());
  speed_limit_detected_callback(SpeedLimitDetected{200L});
  ASSERT_EQ(200L, auto_brake.get_last_speed_limit_mps());
  speed_limit_detected_callback(SpeedLimitDetected{300L});
  ASSERT_EQ(300L, auto_brake.get_last_speed_limit_mps());
}
TEST_F(StrictAutoBrakeTest, NoAlertWhenNotImminent) {
  AutoBrake auto_brake{bus};
  auto_brake.set_collision_threshold_s(2L);
  speed_limit_detected_callback(SpeedLimitDetected{100L});
  speed_update_callback(SpeedUpdate{100L});
  car_detected_callback(CarDetected{1000L, 50L});
}
TEST_F(StrictAutoBrakeTest, AlertWhenImminent) {
  EXPECT_CALL(bus,
              publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(1L))))
      .Times(1);
  AutoBrake auto_brake{bus};
  auto_brake.set_collision_threshold_s(10L);
  speed_limit_detected_callback(SpeedLimitDetected{100L});
  speed_update_callback(SpeedUpdate{100L});
  car_detected_callback(CarDetected{100L, 0L});
}

TEST_F(StrictAutoBrakeTest, NoAlertWhenLimitNotSurpassed) {
  AutoBrake auto_brake{bus};
  speed_limit_detected_callback(SpeedLimitDetected{36L});
  speed_update_callback(SpeedUpdate{35L});
}

TEST_F(StrictAutoBrakeTest, AlertWhenLimitSurpassed) {
  EXPECT_CALL(bus,
              publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(0L))))
      .Times(1);
  AutoBrake auto_brake{bus};
  speed_limit_detected_callback(SpeedLimitDetected{35L});
  speed_update_callback(SpeedUpdate{40L});
}

TEST_F(StrictAutoBrakeTest, AlertWhenNewLowerLimit) {
  EXPECT_CALL(bus,
              publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(0L))))
      .Times(1);
  AutoBrake auto_brake{bus};
  speed_limit_detected_callback(SpeedLimitDetected{35L});
  speed_update_callback(SpeedUpdate{30L});
  speed_limit_detected_callback(SpeedLimitDetected{25L});
}