#pragma once

#include <IFigure.h>
#include <Point.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Представление отрезка в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
struct LineSegment : public IFigure
{
public:
  Point start;
  Point end;

public:
  LineSegment(const Point& startPoint, const Point& endPoint);

  Point Center() const override;
  void Move(const Vector& offset) override;

  double Length() const;
};