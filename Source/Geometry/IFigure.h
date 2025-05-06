#pragma once

#include <functional>
#include <memory>

struct Point;
struct Vector;
class Box;
class OutputStream;
class InputStream;

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
  virtual void Write(OutputStream & os) const = 0;
  /// Возвращает хэш типа фигуры
  virtual constexpr size_t GetTypeHash() const = 0;

  static std::shared_ptr<IFigure> Read(size_t hash);

protected:
  static bool RegisterType(size_t hash, std::function<std::shared_ptr<IFigure>(const InputStream&)>);
};