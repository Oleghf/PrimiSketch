#pragma once

#include <functional>
#include <memory>

struct Point;
struct Vector;
struct Matrix3;
class Box;
class OutputStream;
class InputStream;
class PrimitiveView;

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
  // Трансформирует фигуру
  virtual void Transform(const Matrix3 & transform) = 0;
  /// Записывает данные о фигуре в поток
  virtual void Write(OutputStream & os) const = 0;
  /// Возвращает хэш типа фигуры
  virtual size_t GetTypeHash() const = 0;
  ///
  virtual void Render(PrimitiveView & render) = 0;
  /// Читает данные из потока и в случае успеха возвращает указатель на фигуру, в ином случае nullptr
  static std::shared_ptr<IFigure> Read(InputStream& is);
  /// Регистрирует тип фигуры по хэшу и функции создания соответствующей фигуры
  static bool RegisterType(size_t hash, std::function<std::shared_ptr<IFigure>(InputStream&)>);

};