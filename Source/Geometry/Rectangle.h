#pragma once

#include <IFigure.h>
#include <Point.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Представление прямоугольника в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
class Rectangle : public IFigure
{
public:
  Rectangle(const Point& topLeft, const Point& bottomRight);

  Point TopLeft() const;
  Point TopRight() const;
  Point BottomLeft() const;
  Point BottomRight() const;

  double Top() const;
  double Bottom() const;
  double Right() const;
  double Left() const;

  Point Center() const override;
  void Move(const Vector& offset) override;

private:
  Point m_topLeft;
  Point m_bottomRight;
};