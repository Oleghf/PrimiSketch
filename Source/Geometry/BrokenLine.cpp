#include <limits>
#include <cassert>

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
  Получить массив отрезков, составляющих ломаную линию
*/
//---
std::vector<Point> BrokenLine::GetPoints() const
{
  return m_points;
}
