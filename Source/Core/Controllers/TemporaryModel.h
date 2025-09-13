#pragma once

#include <memory>
#include <functional>

#include <IModel.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Модель временных объектов
/**
*/
////////////////////////////////////////////////////////////////////////////////
class TemporaryModel : public IModel
{
private:
  std::vector<std::shared_ptr<IFigure>> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure) override;
  void Remove(const std::shared_ptr<IFigure> & figure) override;
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) override;
};