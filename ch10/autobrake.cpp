#include "autobrake.h"

AutoBrake::AutoBrake(IServiceBus &bus)
    : collision_threshold_s{5}, speed_mps{},
      last_speed_limit_mps{Initial_speed_limit_mps} {

  bus.subscribe([this, &bus](const SpeedUpdate &update) {
    speed_mps = update.velocity_mps;
    if (speed_mps > last_speed_limit_mps) {
      bus.publish(BrakeCommand{0});
    }
  });

  bus.subscribe([this, &bus](const CarDetected &cd) {
    const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
    const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
    if (time_to_collision_s > 0 &&
        time_to_collision_s <= collision_threshold_s) {
      bus.publish(BrakeCommand{time_to_collision_s});
    }
  });

  bus.subscribe([this, &bus](const SpeedLimitDetected &sl) {
    last_speed_limit_mps = sl.speed_mps;
    if (speed_mps > last_speed_limit_mps) {
      bus.publish(BrakeCommand{0});
    }
  });
}

void AutoBrake::set_collision_threshold_s(double x) {
  if (x < 1.0) {
    throw std::runtime_error{"Collision less than 1."};
  }
  collision_threshold_s = x;
}