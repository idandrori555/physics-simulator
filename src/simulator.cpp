#include "simulator.hpp"
#include "graphics.hpp"
#include <iostream>
#include <thread>

void Simulator::add_object(const Object &object)
{
  m_objects.push_back(object);
}

void Simulator::sleep(double seconds)
{
  std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

void Simulator::run(void)
{
  if (m_objects.empty())
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
  while (running)
  {
    engine.handle_events(running);

    std::cout << *this << std::endl;
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

      // GROUND COLLISION
      if (m_has_ground && o.position.y <= m_ground_y)
      {
        o.position.y = m_ground_y; // Prevent clipping past the floor
        o.velocity.y = -o.velocity.y;
      }
    }

    engine.render(m_objects, *this);
    sleep(consts::time_step);
  }
}

std::vector<Object> &Simulator::get_objects()
{
  return m_objects;
}

void Simulator::set_ground(double y_value)
{
  m_ground_y = y_value;
  m_has_ground = true;
}

double Simulator::get_ground_y() const
{
  return m_ground_y;
}

bool Simulator::has_ground() const
{
  return m_has_ground;
}

std::ostream &operator<<(std::ostream &os, const Simulator &simulator)
{
  size_t idx{1};
  for (const auto &o : simulator.m_objects)
  {
    os << "  Object " << idx++ << ":" << std::endl;
    os << "    mass: " << o.mass << std::endl;
    os << "    position: " << o.position << std::endl;
    os << "    velocity: " << o.velocity << std::endl;
    os << "    acceleration: " << o.acceleration << std::endl;
    os << "    kinetic energy: " << o.kinetic_energy() << std::endl;
    os << "    potential energy: " << o.potential_energy(simulator.get_ground_y()) << std::endl;
    os << "    total energy: " << o.total_energy(simulator.get_ground_y()) << std::endl;
  }
  return os;
}
