#include "../autobrake.h"
#include <gtest/gtest.h>

struct AutoBrakeTest : ::testing::Test {
  // AutoBrake ab{[](const BrakeCommand&){}};
};

TEST_F(AutoBrakeTest, InitialSpeedIsZero) {
  // ASSERT_DOUBLE_EQ(0, ab.get_speed_mps());
}
