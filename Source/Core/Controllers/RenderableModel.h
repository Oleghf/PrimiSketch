#pragma once

#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>

#include <RenderableProperties.h>
#include <IModel.h>
#include <IFigure.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Модель для отрисовки
/**
*/
////////////////////////////////////////////////////////////////////////////////
class RenderableModel : public IModel
{
private:
  std::unordered_map<std::shared_ptr<IFigure>, RenderProperties> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure) override;
  void Remove(const std::shared_ptr<IFigure> & figure) override;
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  std::shared_ptr<IFigure> FindFigure(const Point & point, double radius) const override;

  void SetRenderProperties(std::shared_ptr<IFigure> figure, RenderProperties properties);
  std::optional<RenderProperties> GetRenderProperties(std::shared_ptr<IFigure> figure) const;

};