#pragma once

#include <StyleLine.h>

class Point;

////////////////////////////////////////////////////////////////////////////////
//
/// Интерфейс представления примитивов
/**
*/
////////////////////////////////////////////////////////////////////////////////
class PrimitiveView
{
public:
  virtual void Line(const Point & p1, const Point & p2) = 0;
  virtual void Circle(const Point & center, double radius) = 0;

  virtual void SetPenColor(int r, int g, int b) = 0;
  virtual void SetBrushColor(int r, int g, int b) = 0;
  virtual void SetThickness(double thickness) = 0;
  virtual void SetStyleLine(StyleLine style) = 0;
};