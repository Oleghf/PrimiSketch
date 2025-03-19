#include <cmath>

#include <Point.h>
#include <Vector.h>

namespace
{
constexpr double epsilonDouble = 1e-9;
}


Vector Point::operator-(const Point& rhs) const
{
  return {x - rhs.x, y - rhs.y};
}


Point Point::operator+(const Vector& rhs) const
{
  return {x + rhs.x, y + rhs.y};
}


Point& Point::operator+=(const Vector& rhs)
{
  x += rhs.x;
  y += rhs.y;

  return *this;
}


bool Point::operator==(const Point& rhs) const
{
  return std::abs(x - rhs.x) < epsilonDouble && std::abs(y - rhs.y) < epsilonDouble;
}


bool Point::operator!=(const Point& rhs) const
{
  return !(*this == rhs);
}
