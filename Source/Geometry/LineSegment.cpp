#include <LineSegment.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \param startPoint Начальная точка отрезка
  \param endPoint Конечная точка отрезка
*/
//---
LineSegment::LineSegment(const Point & startPoint, const Point & endPoint)
  : start(startPoint)
  , end(endPoint)
{
}


//------------------------------------------------------------------------------
/**
  \brief Получить центр отрезка
  \return центр отрезка
*/
//---
Point LineSegment::Center() const
{
  double x = (start.x + end.x) / 2;
  double y = (start.y + end.y) / 2;

  return {x, y};
}


//------------------------------------------------------------------------------
/**
  \brief Сдвинуть элемент на вектор
  \param offset вектор смещения
*/
//---
void LineSegment::Move(const Vector& offset)
{
  start += offset;
  end += offset;
}