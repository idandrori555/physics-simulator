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
  // Set ground line right under the spawning point
  instance.set_ground(max_y * 0.03);

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
  // Low floor for a clean high bounce cycle
  instance.set_ground(max_y * 0.03);

  Object obj;
  obj.mass = 1.0;
  obj.position = Vector(max_x * 0.05, max_y * 0.03);
  obj.velocity = Vector(12.0, 16.0);
  obj.add_gravity();

  instance.add_object(obj);
  instance.run();
}

// 4. Terminal Velocity Free-Fall (High Altitude Drop)
auto example_free_fall(void) -> void
{
  // Ground line at the bottom intercepts the high-altitude drop
  instance.set_ground(max_y * 0.03);

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
  // Allows both objects to impact simultaneously and bounce up to their original heights
  instance.set_ground(max_y * 0.03);

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
  // Ground line captures the falling mortars
  instance.set_ground(max_y * 0.03);

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
  // Ground captures the glider when gravity overcomes lift
  instance.set_ground(max_y * 0.03);

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
  // Every separate droplet will impact and bounce cleanly
  instance.set_ground(max_y * 0.03);

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

  // Position the object at the top of the orbit arc
  satellite.position = Vector(center_x, center_y + radius);

  // Give it a perpendicular tangential velocity (moving rightward)
  double speed = 12.0; // Tangential speed in m/s
  satellite.velocity = Vector(speed, 0.0);

  // Apply a dynamic frame-by-frame centripetal force using a conditional force
  double dynamic_force_mag = (satellite.mass * speed * speed) / radius;

  satellite.add_force(
      Vector(0, 0),
      [center_x, center_y, dynamic_force_mag](Object &o) -> bool
      {
        Vector to_center = Vector(center_x, center_y) - o.position;

        double dist = std::sqrt(to_center.x * to_center.x + to_center.y * to_center.y);
        if (dist > 0.001)
        {
          Vector direction = Vector(to_center.x / dist, to_center.y / dist);
          o.sigma_force = direction * dynamic_force_mag;
        }

        return false;
      });

  instance.add_object(satellite);
  instance.run();
}

// 10. Bouncing Ball (Bounce-Back)
auto example_bouncing_ball(void) -> void
{
  // Elevated floor line to visually emphasize the bounce mechanics explicitly
  instance.set_ground(max_y * 0.25);

  Object ball;
  ball.mass = 1.0;
  ball.position = Vector(max_x * 0.2, max_y * 0.8); // Drop from high up
  ball.velocity = Vector(2.0, 0.0);                 // Slight horizontal push
  ball.add_gravity();

  instance.add_object(ball);
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
    std::cerr << " 10: Bouncing Ball (Bounce-Back)" << std::endl;

    return 1;
  }

  const std::array<std::function<void(void)>, 10> examples = {
      example_constant_acceleration,
      example_braking_friction,
      example_parabolic_arc,
      example_free_fall,
      example_galileo_drop,
      example_artillery_crossfire,
      example_headwind_drag,
      example_fountain,
      example_circular_motion,
      example_bouncing_ball,
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
