#include "../include/simulator.hpp"
#include "../include/const.hpp"
#include <iostream>
#include <thread>

// Global access point
Simulator &Simulator::instance()
{
  static Simulator instance;
  return instance;
}

void Simulator::add_object(const Object &object)
{
  Simulator::m_objects.push_back(object);
}

void Simulator::sleep(double seconds)
{
  std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

void Simulator::run(size_t ticks)
{
  if (Simulator::m_objects.empty())
  {
    std::cerr << "No objects to simulate" << std::endl;
    return;
  }

  auto &i = instance();
  while (ticks-- > 0)
  {
    std::cout << i << std::endl;

    for (auto &o : Simulator::m_objects)
    {
      o.acceleration = o.sigma_force / o.mass;

      // 1. Keep track of the old velocity
      Vector old_velocity = o.velocity;

      // 2. Update to the new velocity
      o.velocity += o.acceleration * consts::time_step;

      // 3. Use the average of old and new velocity to update position
      o.position += (old_velocity + o.velocity) * 0.5 * consts::time_step;
    }
    Simulator::sleep(consts::time_step);
  }
}
