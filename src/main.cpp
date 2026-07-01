#include "simulator.hpp"

// Global reference to the engine instance
auto &instance = Simulator::instance();

// 1. Constant Horizontal Acceleration (Rocket Propulsion Simulation)
auto example_constant_acceleration(void) -> void
{
  Object obj;
  obj.mass = 2.0;
  obj.position = Vector(2.0, 5.0);  // Bottom left, off the ground
  obj.velocity = Vector(0.0, 0.0);  // Starts from rest
  obj.add_force(Vector(15.0, 0.0)); // Constant rightward thruster force

  instance.add_object(obj);
  instance.run();
}

// 2. Sliding Block with Kinetic Friction (Braking Simulation)
auto example_braking_friction(void) -> void
{
  Object obj;
  obj.mass = 4.0;
  obj.position = Vector(2.0, 1.0);  // Spawns low on the floor
  obj.velocity = Vector(35.0, 0.0); // High initial horizontal speed
  obj.add_friction(0.4);            // High coefficient of friction (mu = 0.4)

  instance.add_object(obj);
  instance.run();
}

// 3. Classical Projectile Motion (High Parabolic Arc)
auto example_parabolic_arc(void) -> void
{
  Object obj;
  obj.mass = 1.0;
  obj.position = Vector(2.0, 1.0);   // Near bottom-left corner
  obj.velocity = Vector(18.0, 24.0); // Thrown upwards and rightwards
  obj.add_gravity();                 // Downward gravity pulls it into an arc

  instance.add_object(obj);
  instance.run();
}

// 4. Terminal Velocity Free-Fall (High Altitude Drop)
auto example_free_fall(void) -> void
{
  Object obj;
  obj.mass = 1.5;
  obj.position = Vector(20.0, 28.0); // Spawns right at the top center
  obj.velocity = Vector(0.0, 0.0);   // Dropped from rest
  obj.add_gravity();                 // Pulls down natively

  instance.add_object(obj);
  instance.run();
}

// 5. The Galileo Drop Experiment (Verifying Mass Independence in a Vacuum)
auto example_galileo_drop(void) -> void
{
  // Light Object (e.g., Tennis ball)
  Object light_obj;
  light_obj.mass = 0.5;
  light_obj.position = Vector(15.0, 25.0);
  light_obj.add_gravity();

  // Heavy Object (e.g., Massive Anvil) - 100x heavier
  Object heavy_obj;
  heavy_obj.mass = 50.0;
  heavy_obj.position = Vector(25.0, 25.0);
  heavy_obj.add_gravity();

  instance.add_object(light_obj);
  instance.add_object(heavy_obj);
  instance.run();
}

// 6. Artillery Crossfire (Angle Optimization Mechanics)
auto example_artillery_crossfire(void) -> void
{
  // Left Battery: Low, blistering direct-fire shot
  Object alpha;
  alpha.mass = 1.0;
  alpha.position = Vector(1.0, 1.0);
  alpha.velocity = Vector(28.0, 12.0);
  alpha.add_gravity();

  // Right Battery: High, sweeping mortar arc shot
  Object bravo;
  bravo.mass = 1.0;
  bravo.position = Vector(39.0, 1.0);   // Far right edge
  bravo.velocity = Vector(-14.0, 28.0); // Flung up and leftwards
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
  glider.position = Vector(2.0, 20.0); // High mid-air spawn
  glider.velocity = Vector(30.0, 2.0); // Gliding forward with high velocity

  glider.add_gravity();

  // Continuous gale wind force pushing back to the left
  glider.add_force(Vector(-12.0, 0.0));

  instance.add_object(glider);
  instance.run();
}

// 8. Multi-Stage Fountain (Simultaneous Multi-Angle Projection)
auto example_fountain(void) -> void
{
  // Create 5 identical objects launched from the same origin point at different angles
  double velocities_x[5] = {5.0, 10.0, 15.0, 20.0, 25.0};
  double velocities_y[5] = {25.0, 23.0, 20.0, 16.0, 10.0};

  for (int idx = 0; idx < 5; ++idx)
  {
    Object droplet;
    droplet.mass = 1.0;
    droplet.position = Vector(2.0, 1.0); // Bottom-left corner
    droplet.velocity = Vector(velocities_x[idx], velocities_y[idx]);
    droplet.add_gravity();

    instance.add_object(droplet);
  }

  instance.run();
}

int main(void)
{
  // Un-comment the specific scenario you want to visually simulate:

  example_constant_acceleration();
  // example_braking_friction();
  // example_parabolic_arc();
  // example_free_fall();
  // example_galileo_drop();
  // example_artillery_crossfire();
  // example_headwind_drag();
  // example_fountain();

  return 0;
}
