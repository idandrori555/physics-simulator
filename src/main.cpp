#include "../include/simulator.hpp"

auto &instance = Simulator::instance();

template <size_t EXAMPLE>
auto example(void) -> void;

template <>
auto example<1>(void) -> void
{
  Object obj;
  obj.mass = 1;
  obj.add_force(Vector(0, 1));

  instance.add_object(obj);
  instance.run();
}

template <>
auto example<2>(void) -> void
{
  constexpr double mu = 0.1;

  Object obj;
  obj.mass = 1;
  obj.velocity = Vector(10, 0);                  // Initial velocity
  obj.add_force(Vector(mu * obj.normal().y, 0)); // until v=0 (stops)

  instance.add_object(obj);
  instance.run();
}

// === Examples Table ===
// 1. 1D movement, constant acceleration.
// 2. 1D movement, with friction.
// 3. 1D movement, with gravity.
// 4. 2D throw.
// 5. 2D Circular motion.
int main(void)
{
  example<2>();
  return 0;
}
