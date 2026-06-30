#include "../include/vector.hpp"
#include <cmath>

Vector::Vector(double x, double y) : x(x), y(y)
{
}

Vector Vector::from_polar(double size, double angle)
{
  return Vector(size * std::cos(angle), size * std::sin(angle));
}

Vector Vector::operator+(const Vector &other) const
{
  return Vector(x + other.x, y + other.y);
}

Vector &Vector::operator+=(const Vector &other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector &Vector::operator+=(double scalar)
{
  x += scalar;
  y += scalar;
  return *this;
}

Vector Vector::operator-(const Vector &other) const
{
  return Vector(x - other.x, y - other.y);
}

Vector &Vector::operator-=(const Vector &other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector &Vector::operator-=(double scalar)
{
  x -= scalar;
  y -= scalar;
  return *this;
}

Vector Vector::operator*(double scalar) const
{
  return Vector(x * scalar, y * scalar);
}

double Vector::operator*(const Vector &other) const
{
  return x * other.x + y * other.y;
}

Vector Vector::operator/(double scalar) const
{
  return Vector(x / scalar, y / scalar);
}
