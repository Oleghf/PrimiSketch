#pragma once

#include <vector>

#include <IModel.h>

class Box;
class IFigure;

////////////////////////////////////////////////////////////////////////////////
//
/// Модель выделенных фигур
/**
*/
////////////////////////////////////////////////////////////////////////////////
class SelectedModel : public IModel
{
private:
  std::vector<std::shared_ptr<IFigure>> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure) override;
  void Remove(const std::shared_ptr<IFigure> & figure) override;
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  std::shared_ptr<IFigure> FindFigure(const Point & point, double radius) const override;
};
