#include <cmath>

#include <MathUtils.h>
#include <Point.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  ѕерегруженный оператор вычитани€ дл€ точки
*/
//---
Vector Point::operator-(const Point& rhs) const
{
  return {x - rhs.x, y - rhs.y};
}


//------------------------------------------------------------------------------
/**
  ѕерегруженный оператор сложени€ дл€ точки
*/
//---
Point Point::operator+(const Vector& rhs) const
{
  return {x + rhs.x, y + rhs.y};
}


//------------------------------------------------------------------------------
/**
  ѕерегруженный оператор вычитани€ дл€ точки
*/
//---
Point& Point::operator+=(const Vector& rhs)
{
  x += rhs.x;
  y += rhs.y;

  return *this;
}


//------------------------------------------------------------------------------
/**
  ѕерегруженный оператор равенства дл€ точки
*/
//---
bool Point::operator==(const Point& rhs) const
{
  return doubleEQ(x, rhs.x) && doubleEQ(y, rhs.y);
}


//------------------------------------------------------------------------------
/**
  ѕерегруженный оператор неравенства дл€ точки
*/
//---
bool Point::operator!=(const Point& rhs) const
{
  return !(*this == rhs);
}
