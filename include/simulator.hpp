#pragma once

#include "object.hpp"
#include <ostream>
#include <vector>

class Simulator
{
public:
  Simulator(const Simulator &) = delete;
  Simulator &operator=(const Simulator &) = delete;
  Simulator(Simulator &&) = delete;
  Simulator &operator=(Simulator &&) = delete;

  // Global access point
  static Simulator &instance();
  static void add_object(const Object &object);
  static void sleep(double seconds);
  static void run(void);

  const std::vector<Object> &get_objects() const
  {
    return m_objects;
  }

  static void set_ground(double y_value)
  {
    m_ground_y = y_value;
    m_has_ground = true;
  }

  static double get_ground_y()
  {
    return m_ground_y;
  }

  static bool has_ground()
  {
    return m_has_ground;
  }

  friend std::ostream &operator<<(std::ostream &os, const Simulator &simulator)
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
      os << "    potential energy: " << o.potential_energy() << std::endl;
      os << "    total energy: " << o.total_energy() << std::endl;
    }
    return os;
  }

private:
  inline static std::vector<Object> m_objects;
  inline static double m_ground_y{0.0};
  inline static bool m_has_ground{false};

  Simulator() = default;
  ~Simulator() = default;
};
