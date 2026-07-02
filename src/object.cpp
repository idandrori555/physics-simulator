#include "object.hpp"

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

energy_t Object::potential_energy(const double ground_y) const
{
  return mass * std::abs(consts::gravity) * (position.y - ground_y);
}

energy_t Object::total_energy(const double ground_y) const
{
  return kinetic_energy() + potential_energy(ground_y);
}

void Object::add_force(const Vector &force, lambda_t stop_condition)
{
  sigma_force += force;

  if (stop_condition)
    m_conditional_forces.push_back({force, stop_condition});
}

void Object::add_friction(const friction_t friction_mu)
{
  force_t friction_force = force_t(-1 * normal() * friction_mu, 0);
  bool moving_right = velocity.x >= 0;

  if (!moving_right)
    friction_force.x *= -1;

  add_force(friction_force, [moving_right](Object &o)
            {
              bool should_stop = moving_right ? (o.velocity.x <= 0) : (o.velocity.x >= 0);
              if (should_stop)
              {
                o.velocity.x = 0;
                return true;
              }
              return false;
            });
}

void Object::add_gravity(const gravity_t gravity, lambda_t stop_condition)
{
  add_force(Vector(0, -mass * gravity), stop_condition);
}

double Object::normal() const
{
  return consts::gravity * mass;
}
