#include "simulator.hpp"
#include "const.hpp"
#include "graphics.hpp"
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

void Simulator::run(void)
{
  if (Simulator::m_objects.empty())
  {
    std::cerr << "No objects to simulate" << std::endl;
    return;
  }

  GraphicsEngine engine;
  if (!engine.init())
  {
    std::cerr << "Graphics engine failed to initialize" << std::endl;
    return;
  }

  bool running = true;
  auto &i = instance();
  while (running)
  {
    engine.handle_events(running);

    std::cout << i << std::endl;
    for (auto &o : m_objects)
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
      Vector old_velocity = o.velocity;
      o.velocity += o.acceleration * consts::time_step;
      o.position += (old_velocity + o.velocity) * 0.5 * consts::time_step;

      // ---- GROUND COLLISION RESOLUTION ----
      if (m_has_ground && o.position.y <= m_ground_y)
      {
        o.position.y = m_ground_y; // Keep it perfectly on the floor

        // Invert velocity for a bounce (e.g., 0.6 retains 60% of its kinetic energy)
        const double restitution = 0.6;

        if (std::abs(o.velocity.y) > 0.5)
        {
          o.velocity.y = -o.velocity.y * restitution;
        }
        else
        {
          o.velocity.y = 0; // Stop jittering when resting
        }

        // Apply friction to the horizontal speed while sliding on the ground
        o.velocity.x *= 0.98;
      }
    }

    engine.render(m_objects);
    sleep(consts::time_step);
  }
}
