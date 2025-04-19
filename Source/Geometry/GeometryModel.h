#pragma once

#include <vector>
#include <memory>
#include <functional>

#include <IFigure.h>

class Box;

////////////////////////////////////////////////////////////////////////////////
//
/// Геометрическая модель
/**
*/
////////////////////////////////////////////////////////////////////////////////
class GeometryModel
{
private:
  std::vector<std::shared_ptr<IFigure>> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure);
  void Remove(const std::shared_ptr<IFigure> & figure);
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred);
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred);
  std::shared_ptr<IFigure> FindFigure(const Point & point, double radius) const;
};