#include "../include/object.hpp"
#include "../include/const.hpp"

using energy_t = Object::energy_t;
using mass_t = Object::mass_t;
using position_t = Object::position_t;
using velocity_t = Object::velocity_t;
using acceleration_t = Object::acceleration_t;
using force_t = Object::force_t;
using lambda_t = Object::lambda_t;

Object::Object(mass_t mass, const Vector &position, const Vector &velocity)
    : mass(mass), position(position), velocity(velocity)
{
}

Object::Object(mass_t mass, decltype(Vector::x) x, decltype(Vector::y) y, decltype(Vector::x) vx, decltype(Vector::y) vy, decltype(Vector::x) ax, decltype(Vector::y) ay)
    : mass(mass), position(x, y), velocity(vx, vy), acceleration(ax, ay), sigma_force(0, 0)
{
}

energy_t Object::kinetic_energy() const
{
  return 0.5 * mass * (velocity * velocity);
}

energy_t Object::potential_energy() const
{
  return mass * std::abs(consts::gravity.y) * position.y;
}

energy_t Object::total_energy() const
{
  return kinetic_energy() + potential_energy();
}

void Object::add_force(const Vector &force, lambda_t stop_condition)
{
  sigma_force += force;

  if (stop_condition)
  {
    while (!stop_condition(*this))
      ;
    sigma_force -= force;
  }
}

void Object::add_friction(const force_t &friction)
{
  add_force(friction, [](const Object &o)
            {
              return o.velocity.x <= 0;
            });
}

Vector Object::normal() const
{
  return consts::gravity * mass;
}
