#pragma once

#include <vector>

#include <IState.h>
#include <Point.h>

class IView;
class GeometryModel;
class RenderableModel;
class SceneMouseEvent;
class CompleteDrawingEvent;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние создания ломанной кривой
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CreatePolyLineState : public IState
{
private:
  enum class Status
  {
    AwaitActivate,
    AwaitPoints
  };

private:
  std::shared_ptr<IView> m_view;

  GeometryModel & m_geometry;
  RenderableModel & m_renderable;

  Status m_status;

  std::vector<Point> m_points;

  bool m_isAutoBuild;

private:
  std::unique_ptr<ICommand> OnSceneMouseEvent(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> OnCompleteDrawingEvent(const CompleteDrawingEvent & ev);

  std::unique_ptr<ICommand> CreateDrawCommand(const std::vector<Point> & points);

public:
  CreatePolyLineState(std::shared_ptr<IView> view, GeometryModel & geometry, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};