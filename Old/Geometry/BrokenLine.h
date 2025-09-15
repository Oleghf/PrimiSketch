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
  bool InBox(const Box& box) const override;
  bool IntersectsPoint(const Point & point, double epsilon) const override;
  void Write(OutputStream & os) const override;
  size_t GetTypeHash() const override;
  void Render(PrimitiveView & view) override;

  static std::shared_ptr<BrokenLine> Read(InputStream & is);

  void Update(const std::vector<Point> & points);

  std::vector<Point> GetPoints() const;
};