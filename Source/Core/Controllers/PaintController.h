#pragma once

#include <memory>

class IView;
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
  GeometryModel & m_geometry;

public:
  PaintController(std::shared_ptr<IView> view, GeometryModel & geometry);

  void OnPaintEvent(const ScenePaintEvent & event);
};