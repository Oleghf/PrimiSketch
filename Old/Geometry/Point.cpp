#include <cmath>

#include <MathUtils.h>
#include <Point.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  Перегруженный оператор вычитания для точки
*/
//---
Vector Point::operator-(const Point& rhs) const
{
  return {x - rhs.x, y - rhs.y};
}


//------------------------------------------------------------------------------
/**
  Перегруженный оператор сложения для точки
*/
//---
Point Point::operator+(const Vector& rhs) const
{
  return {x + rhs.dx, y + rhs.dy};
}


//------------------------------------------------------------------------------
/**
  Перегруженный оператор вычитания для точки
*/
//---
Point& Point::operator+=(const Vector& rhs)
{
  x += rhs.dx;
  y += rhs.dy;

  return *this;
}


//------------------------------------------------------------------------------
/**
  Перегруженный оператор равенства для точки
*/
//---
bool Point::operator==(const Point& rhs) const
{
  return math_utils::doubleEQ(x, rhs.x) && math_utils::doubleEQ(y, rhs.y);
}


//------------------------------------------------------------------------------
/**
  Перегруженный оператор неравенства для точки
*/
//---
bool Point::operator!=(const Point& rhs) const
{
  return !(*this == rhs);
}
