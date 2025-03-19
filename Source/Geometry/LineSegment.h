#pragma once

#include <IFigure.h>
#include <Point.h>

////////////////////////////////////////////////////////////////////////////////
//
/// ѕредставление отрезка в 2D пространстве
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

  bool operator==(const LineSegment& rhs) const;
  bool operator!=(const LineSegment& rhs) const;

  Point Center() const override;
  void Move(const Vector& offset) override;
};