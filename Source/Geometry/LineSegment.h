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
  void Move(const Vector & offset) override;
  bool InBox(const Box & box) const override;
  bool IntersectsPoint(const Point & point, double epsilon) const override;
  void Write(OutputStream & os) const override;
  size_t GetTypeHash() const override;

  static std::shared_ptr<LineSegment> Read(const InputStream & is);
  double Length() const;
};