#pragma once

#include <memory>

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
private:
  Point m_topLeft;
  Point m_bottomRight;

public:
  Rectangle(const Point & first, const Point & second);
  
  Point Center() const override;
  void Move(const Vector & offset) override;
  bool InBox(const Box & box) const override;
  bool IntersectsPoint(const Point & point, double epsilon) const override;
  void Write(OutputStream & os) const override;
  size_t GetTypeHash() const override;
  void Render(PrimitiveView & view) override;

  static std::shared_ptr<Rectangle> Read(InputStream & is);

  void Update(const Point & first, const Point & second);

  Point TopLeft() const;
  Point TopRight() const;
  Point BottomLeft() const;
  Point BottomRight() const;

  double Top() const;
  double Bottom() const;
  double Right() const;
  double Left() const;
}; 