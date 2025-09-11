#pragma once

#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>

#include <RenderableProperties.h>
#include <IModel.h>
#include <StyleLine.h>

class IFigure;

////////////////////////////////////////////////////////////////////////////////
//
/// Модель для отрисовки
/**
*/
////////////////////////////////////////////////////////////////////////////////
class RenderableModel : public IModel
{
private:
  std::unordered_map<std::shared_ptr<IFigure>, RenderableProperties> m_figures;

public:
  void Add(std::shared_ptr<IFigure> figure) override;
  void Remove(const std::shared_ptr<IFigure> & figure) override;
  void ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred) override;
  void ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred) override;

  void SetRenderProperties(std::shared_ptr<IFigure> figure, RenderableProperties properties);
  std::optional<RenderableProperties> GetRenderProperties(std::shared_ptr<IFigure> figure) const;

};