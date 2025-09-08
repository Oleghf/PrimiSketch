#pragma once

#include <PrimitiveView.h>

class QPainter;

////////////////////////////////////////////////////////////////////////////////
//
/// Обертка QPainter
/**
*/
////////////////////////////////////////////////////////////////////////////////
class QtPainter : public PrimitiveView
{
private:
  QPainter & m_painter;

public:
  QtPainter(QPainter & qpainter);

  void Line(const Point & p1, const Point & p2) override;
  void Circle(const Point & center, double radius) override;
};