#include <algorithm>

#include <Box.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор

  \details Создает box по двум точкам.
  Автоматически корректирует координаты так, чтобы m_topLeft
  всегда была верхней левой точкой, а m_bottomRight - нижней правой

  \param first любая точка box
  \param second любая точка box

  \warning Передача одинаковых точек создаст вырожденный box
*/
//---
Box::Box(const Point & first, const Point & second)
  : m_topLeft({std::min(first.x, second.x), std::max(first.y, second.y)})
  , m_bottomRight({std::max(first.x, second.x), std::min(first.y, second.y)})
{
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю левую точку
*/
//---
Point Box::TopLeft() const
{
  return m_topLeft;
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю правую точку
*/
//---
Point Box::TopRight() const
{
  return {m_bottomRight.x, m_topLeft.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю левую точку
*/
//---
Point Box::BottomLeft() const
{
  return {m_topLeft.x, m_bottomRight.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю правую точку
*/
//---
Point Box::BottomRight() const
{
  return m_bottomRight;
}
