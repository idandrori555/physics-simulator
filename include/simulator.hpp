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

  static std::vector<Object> &get_objects();

  // Ground collision control
  static void set_ground(double y_value);
  static double get_ground_y();
  static bool has_ground();

  friend std::ostream &operator<<(std::ostream &os, const Simulator &simulator);

private:
  inline static std::vector<Object> m_objects;
  inline static double m_ground_y{0.0};
  inline static bool m_has_ground{false};

  Simulator() = default;
  ~Simulator() = default;
};
