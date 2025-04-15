#pragma once

#include <vector>
#include <memory>

#include <IFigure.h>

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
  void add(std::shared_ptr<IFigure> figure);
  void remove(const std::shared_ptr<IFigure> & figure);
  std::shared_ptr<IFigure> findFigure(const Point & point, double radius) const;
};