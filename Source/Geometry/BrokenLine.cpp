#include <limits>
#include <cassert>
#include <algorithm>

#include <ConsoleOutputStream.h>
#include <OutputStream.h>
#include <MathUtils.h>
#include <Vector.h>
#include <BrokenLine.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \param points Массив точек
  \warning Массив всегда должен содержать хотя бы одну точку
*/
//---
BrokenLine::BrokenLine(const std::vector<Point> & points)
	: m_points(points)
{
  assert(points.size() > 0);
}


//------------------------------------------------------------------------------
/**
  \brief Получить центр ломаной линии
  \details Высчитывает центр ломанной линии
*/
//---
Point BrokenLine::Center() const
{
  double minX = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double minY = std::numeric_limits<double>::max();
  double maxY = std::numeric_limits<double>::lowest();

  for (const Point& point : m_points)
  {
    minX = std::min(minX, point.x);
    maxX = std::max(maxX, point.x);
    minY = std::min(minY, point.y);
    maxY = std::max(maxY, point.y);
  }

  return {{(minX + maxX) / 2}, {(minY + maxY) / 2}};
}


//------------------------------------------------------------------------------
/**
  \brief Сдвинуть ломаную на вектор
  \param offset вектор смещения
*/
//---
void BrokenLine::Move(const Vector & offset)
{
  for (Point & point : m_points)
    point += offset;
}


//------------------------------------------------------------------------------
/**
  Проверить, нахождение ломанной линии в прямоугольной области
*/
//---
bool BrokenLine::InBox(const Box& box) const
{
  return std::ranges::all_of(m_points, [&box](const Point & point) { return math_utils::PointInBox(point, box); });
}


//------------------------------------------------------------------------------
/**
  \brief Проверить вхождение точки (с погрешностью) в ломанную линию
  \param point Точка с которой проверяется пересечение
  \param epsilon Допустимая погрешность
*/
//---
bool BrokenLine::IntersectsPoint(const Point & point, double epsilon) const
{
  for (size_t i = 1; i < m_points.size(); i++)
  {
    if (math_utils::SegmentIntersectsCircle(m_points[i - 1], m_points[i], point, epsilon))
      return true;
  }
  return false;
}


//------------------------------------------------------------------------------
/**
  Выводит данные о ломанной линии в численном формате
*/
//---
void BrokenLine::Write(OutputStream& os) const
{
  os.Write(static_cast<int>(m_points.size()));

  std::ranges::for_each(m_points,
                        [&os](const Point & point)
                        {
                          os.Write(point.x);
                          os.Write(point.y);
                        });
}


//------------------------------------------------------------------------------
/**
  Возвращает хэш типа ломанной линии
*/
//---
constexpr size_t BrokenLine::GetTypeHash() const
{
  return math_utils::hash("BrokenLine");
}


//------------------------------------------------------------------------------
/**
  Получить массив отрезков, составляющих ломаную линию
*/
//---
std::vector<Point> BrokenLine::GetPoints() const
{
  return m_points;
}
