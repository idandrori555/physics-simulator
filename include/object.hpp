#pragma once

#include "const.hpp"
#include "types.hpp"
#include "vector.hpp"

struct Object
{
  mass_t mass{1};
  position_t position{0, 0};
  velocity_t velocity{0, 0};
  acceleration_t acceleration{0, 0};
  force_t sigma_force{0, 0};
  std::vector<std::pair<force_t, lambda_t>> m_conditional_forces;

  Object() = default;
  Object(mass_t mass, const Vector &position, const Vector &velocity);

  Object(mass_t mass, decltype(Vector::x) x = 0, decltype(Vector::y) y = 0, decltype(Vector::x) vx = 0, decltype(Vector::y) vy = 0, decltype(Vector::x) ax = 0, decltype(Vector::y) ay = 0);

  energy_t kinetic_energy() const;
  energy_t potential_energy() const;
  energy_t total_energy() const;

  void add_force(const Vector &force, lambda_t stop_condition = nullptr);
  void add_friction(const friction_t friction_mu);
  void add_gravity(const gravity_t gravity = consts::gravity, lambda_t stop_condition = nullptr);

  Vector normal() const;
};
