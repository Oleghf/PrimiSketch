#include <algorithm>

#include <Rectangle.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор

  \details Создает прямоугольник по двум точкам.
  Автоматически корректирует координаты так, чтобы m_topLeft
  всегда была верхней левой точкой, а m_bottomRight - нижней правой

  \param topLeft Левая верхняя точка прямоугольника или любая другая точка прямоугольника
  \param bottomRight Правая нижняя точка прямоугольника или любая другая точка прямоугольника

  \warning Передача одинаковых точек создаст вырожденный прямоугольник
*/
//---
Rectangle::Rectangle(const Point & topLeft, const Point & bottomRight)
  : m_topLeft({std::min(topLeft.x, bottomRight.x), std::max(topLeft.y, bottomRight.y)})
  , m_bottomRight({std::max(topLeft.x, bottomRight.x), std::min(topLeft.y, bottomRight.y)})
{
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю левую точку
*/
//---
Point Rectangle::TopLeft() const
{
  return m_topLeft;
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю правую точку
*/
//---
Point Rectangle::TopRight() const
{
  return {m_bottomRight.x, m_topLeft.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю левую точку
*/
//---
Point Rectangle::BottomLeft() const
{
  return {m_topLeft.x, m_bottomRight.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю правую точку
*/
//---
Point Rectangle::BottomRight() const
{
  return m_bottomRight;
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю границу прямоугольника по y
*/
//---
double Rectangle::Top() const
{
  return m_topLeft.y;
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю границу прямоугольника по y
*/
//---
double Rectangle::Bottom() const
{
  return m_bottomRight.y;
}


//------------------------------------------------------------------------------
/**
  Получить правую границу прямоугольника по x
*/
//---
double Rectangle::Right() const
{
  return m_bottomRight.x;
}


//------------------------------------------------------------------------------
/**
  Получить левую границу прямоугольника по x
*/
//---
double Rectangle::Left() const
{
  return m_topLeft.x;
}


//------------------------------------------------------------------------------
/**
  Получить центр прямоугольника
*/
//---
Point Rectangle::Center() const
{
  double x = (m_topLeft.x + m_bottomRight.x) / 2;
  double y = (m_topLeft.y + m_bottomRight.y) / 2;

  return {x, y};
}


//------------------------------------------------------------------------------
/**
  \brief Сдвинуть прямоугольник на вектор
  \param offset Вектор смещения
*/
//---
void Rectangle::Move(const Vector & offset)
{
  m_topLeft += offset;
  m_bottomRight += offset;
}
