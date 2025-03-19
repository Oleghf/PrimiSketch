#include <cmath>

#include <Vector.h>


Vector Vector::operator+(const Vector& rhs) const
{
  return {x + rhs.x, y + rhs.y};
}


Vector& Vector::operator+=(const Vector& rhs)
{
  x += rhs.x;
  y += rhs.y;

  return *this;
}


Vector Vector::operator-(const Vector& rhs) const
{
  return {x - rhs.x, y - rhs.y};
}


Vector& Vector::operator-=(const Vector& rhs)
{
  x -= rhs.x;
  y -= rhs.y;

  return *this;
}


Vector Vector::operator*(double rhs) const
{
  return {x * rhs, y * rhs};
}


Vector& Vector::operator*=(double rhs)
{
  x *= rhs;
  y *= rhs;

  return *this;
}


bool Vector::operator==(const Vector& rhs) const
{
  return x == rhs.x && y == rhs.y;
}


bool Vector::operator!=(const Vector& rhs) const
{
  return !(*this == rhs);
}


double Vector::Length() const
{
  return std::sqrt(x * x + y * y);
}
