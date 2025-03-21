#pragma once

#include <vector>

#include <IFigure.h>
#include <LineSegment.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Представление ломаной линии в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
class BrokenLine : public IFigure
{
private:
  std::vector<LineSegment> m_segments;

public:
  BrokenLine(const std::vector<LineSegment> & segments);

  Point Center() const override;
  void Move(const Vector & offset) override;

  std::vector<LineSegment> GetSegments() const;
  bool IsClosed() const;
  double Length() const;
};