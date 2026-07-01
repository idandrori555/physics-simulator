#include "const.hpp"
#include "simulator.hpp"
#include <array>
#include <cmath>
#include <functional>
#include <iostream>

// Global reference to the engine instance
auto &instance = Simulator::instance();

// Helper constants for fractional scaling relative to world dimensions
const double max_x = static_cast<double>(consts::SCREEN_WIDTH) / consts::METERS_TO_PIXELS;
const double max_y = static_cast<double>(consts::SCREEN_HEIGHT) / consts::METERS_TO_PIXELS;

// 1. Constant Horizontal Acceleration (Rocket Propulsion Simulation)
auto example_constant_acceleration(void) -> void
{
  Object obj;
  obj.mass = 2.0;
  obj.position = Vector(max_x * 0.05, max_y * 0.15); // Bottom-left off the floor
  obj.velocity = Vector(0.0, 0.0);
  obj.add_force(Vector(15.0, 0.0));

  instance.add_object(obj);
  instance.run();
}

// 2. Sliding Block with Kinetic Friction (Braking Simulation)
auto example_braking_friction(void) -> void
{
  Object obj;
  obj.mass = 4.0;
  obj.position = Vector(max_x * 0.05, max_y * 0.03); // Low on the floor
  obj.velocity = Vector(20.0, 0.0);                  // High initial horizontal speed
  obj.add_friction(0.4);

  instance.add_object(obj);
  instance.run();
}

// 3. Classical Projectile Motion (High Parabolic Arc)
auto example_parabolic_arc(void) -> void
{
  Object obj;
  obj.mass = 1.0;
  obj.position = Vector(max_x * 0.05, max_y * 0.03);
  obj.velocity = Vector(18.0, 24.0);
  obj.add_gravity();

  instance.add_object(obj);
  instance.run();
}

// 4. Terminal Velocity Free-Fall (High Altitude Drop)
auto example_free_fall(void) -> void
{
  Object obj;
  obj.mass = 1.5;
  obj.position = Vector(max_x * 0.50, max_y * 0.93); // Top center
  obj.velocity = Vector(0.0, 0.0);
  obj.add_gravity();

  instance.add_object(obj);
  instance.run();
}

// 5. The Galileo Drop Experiment (Verifying Mass Independence in a Vacuum)
auto example_galileo_drop(void) -> void
{
  // Light Object
  Object light_obj;
  light_obj.mass = 0.5;
  light_obj.position = Vector(max_x * 0.35, max_y * 0.83);
  light_obj.add_gravity();

  // Heavy Object - 100x heavier
  Object heavy_obj;
  heavy_obj.mass = 50.0;
  heavy_obj.position = Vector(max_x * 0.65, max_y * 0.83);
  heavy_obj.add_gravity();

  instance.add_object(light_obj);
  instance.add_object(heavy_obj);
  instance.run();
}

// 6. Artillery Crossfire (Angle Optimization Mechanics)
auto example_artillery_crossfire(void) -> void
{
  // Left Battery
  Object alpha;
  alpha.mass = 1.0;
  alpha.position = Vector(max_x * 0.025, max_y * 0.03);
  alpha.velocity = Vector(14.0, 28.0);
  alpha.add_gravity();

  // Right Battery
  Object bravo;
  bravo.mass = 1.0;
  bravo.position = Vector(max_x * 0.975, max_y * 0.03);
  bravo.velocity = Vector(-14.0, 28.0);
  bravo.add_gravity();

  instance.add_object(alpha);
  instance.add_object(bravo);
  instance.run();
}

// 7. Constant Headwind Drag (Dynamic Balancing Forces)
auto example_headwind_drag(void) -> void
{
  Object glider;
  glider.mass = 1.0;
  glider.position = Vector(max_x * 0.05, max_y * 0.65);
  glider.velocity = Vector(30.0, 2.0);
  glider.add_gravity();
  glider.add_force(Vector(-12.0, 0.0));

  instance.add_object(glider);
  instance.run();
}

// 8. Multi-Stage Fountain (Simultaneous Multi-Angle Projection)
auto example_fountain(void) -> void
{
  double velocities_x[5] = {5.0, 10.0, 15.0, 20.0, 25.0};
  double velocities_y[5] = {25.0, 23.0, 20.0, 16.0, 10.0};

  for (int idx = 0; idx < 5; ++idx)
  {
    Object droplet;
    droplet.mass = 1.0;
    droplet.position = Vector(max_x * 0.05, max_y * 0.03);
    droplet.velocity = Vector(velocities_x[idx], velocities_y[idx]);
    droplet.add_gravity();

    instance.add_object(droplet);
  }

  instance.run();
}

// 9. Uniform Circular Motion Simulation (Orbital Mechanics)
auto example_circular_motion(void) -> void
{
  Object satellite;
  satellite.mass = 1.0;

  // Set the orbit center to the middle of your screen space
  double center_x = max_x * 0.5;
  double center_y = max_y * 0.5;
  double radius = 8.0; // 8 meters orbital radius

  // 1. Position the object at the top of the orbit arc
  satellite.position = Vector(center_x, center_y + radius);

  // 2. Give it a perpendicular tangential velocity (moving rightward)
  double speed = 12.0; // Tangential speed in m/s
  satellite.velocity = Vector(speed, 0.0);

  // 3. Apply a dynamic frame-by-frame centripetal force using a conditional force
  // We use the lambda to compute the force vector pointing back to the center every frame.
  double dynamic_force_mag = (satellite.mass * speed * speed) / radius;

  satellite.add_force(
      Vector(0, 0), // Base vector (unused since we update it dynamically or via a custom hook)
      [center_x, center_y, dynamic_force_mag](Object &o) -> bool
      {
        // Calculate vector from object pointing directly to the center
        Vector to_center = Vector(center_x, center_y) - o.position;

        // Normalize the vector to get the direction
        double dist = std::sqrt(to_center.x * to_center.x + to_center.y * to_center.y);
        if (dist > 0.001)
        {
          Vector direction = Vector(to_center.x / dist, to_center.y / dist);

          // Re-assign the active pull force toward the center
          o.sigma_force = direction * dynamic_force_mag;
        }

        return false; // Return false so this force tracker never stops/expires
      });

  instance.add_object(satellite);
  instance.run();
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <scenario>" << std::endl;
    std::cerr << "Available scenarios:" << std::endl;
    std::cerr << "  1: Constant Horizontal Acceleration" << std::endl;
    std::cerr << "  2: Sliding Block with Kinetic Friction" << std::endl;
    std::cerr << "  3: Classical Projectile Motion" << std::endl;
    std::cerr << "  4: Terminal Velocity Free-Fall" << std::endl;
    std::cerr << "  5: The Galileo Drop Experiment" << std::endl;
    std::cerr << "  6: Artillery Crossfire" << std::endl;
    std::cerr << "  7: Constant Headwind Drag" << std::endl;
    std::cerr << "  8: Multi-Stage Fountain" << std::endl;
    std::cerr << "  9: Uniform Circular Motion Simulation" << std::endl;

    return 1;
  }

  const std::array<std::function<void(void)>, 9> examples = {
      example_constant_acceleration,
      example_braking_friction,
      example_parabolic_arc,
      example_free_fall,
      example_galileo_drop,
      example_artillery_crossfire,
      example_headwind_drag,
      example_fountain,
      example_circular_motion,
  };

  size_t exampleToRun = std::stoi(argv[1]);
  if (exampleToRun < 1 || exampleToRun > examples.size())
  {
    std::cerr << "Invalid example number: " << exampleToRun << std::endl;
    return 1;
  }

  examples.at(exampleToRun - 1)();

  return 0;
}
