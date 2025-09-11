#pragma once

#include <memory>
#include <unordered_map>

class IView;
class RenderableModel;
class GeometryModel;
class ScenePaintEvent;


////////////////////////////////////////////////////////////////////////////////
//
/// Контроллер отрисовки
/**
*/
////////////////////////////////////////////////////////////////////////////////
class PaintController
{
private:
  std::shared_ptr<IView> m_view;
  RenderableModel & m_renderable;

public:
  PaintController(std::shared_ptr<IView> view, RenderableModel & renderable);

  void OnPaintEvent(const ScenePaintEvent & event);
};