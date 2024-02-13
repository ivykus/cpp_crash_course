#ifndef AUTOBRAKE_HPP
#define AUTOBRAKE_HPP

#include <functional>
#include <stdexcept>
#include <string>
struct SpeedUpdate {
  double velocity_mps;
};

struct CarDetected {
  double distance_m;
  double velocity_mps;
};

struct BrakeCommand {
  double time_to_collision_s;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate &)>;
using CarDetectedCallback = std::function<void(const CarDetected &)>;

struct IServiceBus {
  virtual ~IServiceBus() = default;
  virtual void publish(const BrakeCommand &) = 0;
  virtual void subscribe(SpeedUpdateCallback) = 0;
  virtual void subscribe(CarDetectedCallback) = 0;
};

struct AutoBrake {

  AutoBrake(IServiceBus &bus);

  void set_collision_threshold_s(double x);
  double get_collision_threshold_s() const { return collision_threshold_s; }

  double get_speed_mps() const { return speed_mps; }

private:
  double collision_threshold_s;
  double speed_mps;
};

#endif