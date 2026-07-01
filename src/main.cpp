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

int main(void)
{
  example_2();
  return 0;
}
