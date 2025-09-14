#pragma once

#include <memory>
#include <functional>

struct Point;
class Box;
class IFigure;

////////////////////////////////////////////////////////////////////////////////
//
/// Интерфейс модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
class IModel
{
public:
  /// Добавить фигуру
  virtual void Add(std::shared_ptr<IFigure> figure) = 0;
  /// Удалить фигуру
  virtual void Remove(const std::shared_ptr<IFigure> & figure) = 0;
  /// forEach по фигурам
  virtual void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) = 0;
  /// forEach по фигурам в переданной прямоугольной области
  virtual void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) = 0;
  /// Находит первую попавшуюся фигуру в точке в определенном радиусом
  virtual std::shared_ptr<IFigure> FindFigure(const Point & point, double radius) const = 0;
};