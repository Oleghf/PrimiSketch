#pragma once

struct Point;
struct Vector;
class Box;
class OutputStream;

////////////////////////////////////////////////////////////////////////////////
//
/// Базовый класс фигуры
/**
*/
////////////////////////////////////////////////////////////////////////////////
class IFigure
{
public:
  /// Центр фигуры
  virtual Point Center() const = 0;
  /// Сдвинуть фигуру
  virtual void Move(const Vector& offset) = 0;
  /// Проверка нахождения фигуры в прямоугольной области
  virtual bool InBox(const Box& box) const = 0;
  /// Проверка пересечения фигуры с точкой
  virtual bool IntersectsPoint(const Point & point, double epsilon) const = 0;
  /// Записывает данные о фигуре в поток
  virtual void Write(OutputStream & os) = 0;
};