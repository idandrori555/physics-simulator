#include "simulator.hpp"

auto &instance = Simulator::instance();

auto example_1(void) -> void
{
  Object obj;
  obj.mass = 1;
  obj.add_force(Vector(0, 1));

  instance.add_object(obj);
  instance.run();
}

auto example_2(void) -> void
{
  Object obj;
  obj.mass = 1;
  obj.velocity = Vector(10, 0); // Initial velocity
  obj.add_friction(0.3);        // mu = .3

  instance.add_object(obj);
  instance.run();
}

auto example_3(void) -> void
{
  Object obj;
  obj.mass = 1;
  obj.position = Vector(0, 0); // start off at origin
  obj.velocity = Vector(3, 3); // 45 degree angle off the ground, angled throw.
  obj.add_gravity();

  instance.add_object(obj);
  instance.run();
}

int main(void)
{
  example_3();
  return 0;
}
