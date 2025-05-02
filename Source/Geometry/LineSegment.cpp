#include <algorithm>

#include <OutputStream.h>
#include <MathUtils.h>
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


//------------------------------------------------------------------------------
/**
  Получить длину отрезка
*/
//---
double LineSegment::Length() const
{
  return (end - start).Length();
}


//------------------------------------------------------------------------------
/**
  \brief Проверить, нахождение отрезка в прямоугольной области
  \param topLeft Верхний левый угол прямоугольной области
  \param bottomRight Правый нижний угол прямоугольной области
*/
//---
bool LineSegment::InBox(const Box & box) const
{
  const double minX = std::min(start.x, end.x);
  const double minY = std::min(start.y, end.y);
  const double maxX = std::max(start.x, end.x);
  const double maxY = std::max(start.y, end.y);

  const Point topLeftBox = box.TopLeft();
  const Point bottomRightBox = box.BottomRight();

  return (minX >= topLeftBox.x && maxX <= bottomRightBox.x) &&
         (minY >= bottomRightBox.y && maxY <= topLeftBox.y);
}


//------------------------------------------------------------------------------
/**
  \brief Проверяет вхождение точки (с погрешностью) в отрезок
  \param point Точка с которой проверяется пересечение
  \param epsilon Допустимая погрешность
*/
//---
bool LineSegment::IntersectsPoint(const Point & point, double epsilon) const
{
  return math_utils::SegmentIntersectsCircle(start, end, point, epsilon);
}


//------------------------------------------------------------------------------
/**
  Выводит данные об отрезке в численном формате
*/
//---
void LineSegment::Write(OutputStream & os) const
{
  os.Write(start.x);
  os.Write(start.y);
  os.Write(end.x);
  os.Write(end.y);
}


//------------------------------------------------------------------------------
/**
  Возвращает хэш типа отрезка
*/
//---
constexpr size_t LineSegment::GetTypeHash() const
{
  return math_utils::hash("LineSegment");
}
