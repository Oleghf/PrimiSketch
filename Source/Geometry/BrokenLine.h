#pragma once

#include <vector>

#include <IFigure.h>
#include <Point.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Представление ломаной линии в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
class BrokenLine : public IFigure
{
private:
  std::vector<Point> m_points;

public:
  BrokenLine(const std::vector<Point> & points);

  Point Center() const override;
  void Move(const Vector & offset) override;

  std::vector<Point> GetPoints() const;
};