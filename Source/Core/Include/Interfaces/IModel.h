#pragma once

#include <memory>

#include <IFigure.h>

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
};