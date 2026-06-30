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
      // Remove any forces that are no longer valid
      std::erase_if(o.m_conditional_forces, [&](auto &pair)
                    {
                      auto &[force, stop_condition] = pair;
                      if (stop_condition(o))
                      {
                        o.sigma_force -= force;
                        return true;
                      }
                      return false;
                    });

      o.acceleration = o.sigma_force / o.mass;

      // Keep track of the old velocity
      Vector old_velocity = o.velocity;

      // Update to the new velocity
      o.velocity += o.acceleration * consts::time_step;

      // Use the average of old and new velocity to update position
      o.position += (old_velocity + o.velocity) * 0.5 * consts::time_step;
    }
    Simulator::sleep(consts::time_step);
  }
}
