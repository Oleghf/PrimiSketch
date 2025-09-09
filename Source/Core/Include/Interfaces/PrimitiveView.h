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
  /// Отрисовать линию по двум точкам
  virtual void Line(const Point & p1, const Point & p2) = 0;
  /// Отрисовать окружность по центру и радиусу
  virtual void Circle(const Point & center, double radius) = 0;

  /// Установить цвет обводки
  virtual void SetPenColor(int r, int g, int b) = 0;
  /// Установить цвет заливки
  virtual void SetBrushColor(int r, int g, int b) = 0;
  /// Установить толщину обводки
  virtual void SetThickness(double thickness) = 0;
  /// Установить стиль отрисовки
  virtual void SetStyleLine(StyleLine style) = 0;
};