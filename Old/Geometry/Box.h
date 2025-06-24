#pragma once

#include <Point.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Представление обрамляющего прямоугольника
/**
*/
////////////////////////////////////////////////////////////////////////////////
class Box
{
private:
  Point m_topLeft;
  Point m_bottomRight;

public:
  Box(const Point & first, const Point & second);

  Point TopLeft() const;
  Point TopRight() const;
  Point BottomLeft() const;
  Point BottomRight() const;
};