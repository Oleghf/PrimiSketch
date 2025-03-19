#include <Point.h>
#include <Vector.h>


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
  return x == rhs.x && y == rhs.y;
}


bool Point::operator!=(const Point& rhs) const
{
  return !(*this == rhs);
}
