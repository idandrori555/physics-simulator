#include "../include/object.hpp"
#include "../include/const.hpp"

using energy_t = Object::energy_t;
using mass_t = Object::mass_t;
using position_t = Object::position_t;
using velocity_t = Object::velocity_t;
using acceleration_t = Object::acceleration_t;
using force_t = Object::force_t;
using friction_t = Object::friction_t;
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
    m_conditional_forces.push_back({force, stop_condition});
}

void Object::add_friction(const friction_t friction_mu)
{
  force_t friction_force = force_t(normal().y * friction_mu, 0);
  if (velocity.x < 0)
    friction_force.x *= -1;

  add_force(friction_force, [](Object &o)
            {
              if (o.velocity.x <= 0)
              {
                o.velocity.x = 0; // reset velocity to 0
                return true;
              }
              return false;
            });
}

Vector Object::normal() const
{
  return consts::gravity * mass;
}
