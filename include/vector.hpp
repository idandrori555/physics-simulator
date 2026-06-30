#pragma once

#include <ostream>

struct Vector
{
  double x;
  double y;

  Vector(double x = 0, double y = 0);
  static Vector from_polar(double size, double angle);

  Vector operator+(const Vector &other) const;
  Vector &operator+=(const Vector &other);
  Vector &operator+=(double scalar) = delete;

  Vector operator-(const Vector &other) const;
  Vector &operator-=(const Vector &other);
  Vector &operator-=(double scalar) = delete;

  Vector operator*(double scalar) const;
  double operator*(const Vector &other) const;

  Vector operator/(double scalar) const;

  friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
  {
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
  }
};
