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
  virtual void Add(std::shared_ptr<IFigure> figure) = 0;
  virtual void Remove(const std::shared_ptr<IFigure> & figure) = 0;
  virtual void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) = 0;
  virtual void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) = 0;
};