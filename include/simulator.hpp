#pragma once

#include "object.hpp"
#include <ostream>
#include <vector>

class Simulator
{
public:
  // Simulator(const Simulator &) = delete;
  // Simulator &operator=(const Simulator &) = delete;
  // Simulator(Simulator &&) = delete;
  // Simulator &operator=(Simulator &&) = delete;

  void add_object(const Object &object);
  void sleep(double seconds);
  void run(void);

  std::vector<Object> &get_objects();

  // Ground collision control
  void set_ground(double y_value);
  double get_ground_y() const;
  bool has_ground() const;

  friend std::ostream &operator<<(std::ostream &os, const Simulator &simulator);

private:
  std::vector<Object> m_objects{};
  double m_ground_y{0.0};
  bool m_has_ground{false};
};
