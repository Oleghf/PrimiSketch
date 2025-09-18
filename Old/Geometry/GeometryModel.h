#pragma once

#include <vector>
#include <memory>
#include <functional>

#include <IModel.h>
#include <IFigure.h>

class Box;

////////////////////////////////////////////////////////////////////////////////
//
/// Геометрическая модель
/**
*/
////////////////////////////////////////////////////////////////////////////////
class GeometryModel : public IModel
{
private:
  std::vector<std::shared_ptr<IFigure>> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure) override;
  void Remove(const std::shared_ptr<IFigure> & figure) override;
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  std::shared_ptr<IFigure> FindFigure(const Point & point, double radius) const override;
  void Write(OutputStream & os);
};