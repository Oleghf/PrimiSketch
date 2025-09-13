#pragma once

#include <memory>

#include <IState.h>
#include <Point.h>

class LineSegment;
class SceneMouseEvent;
class CompleteDrawingEvent;
class AutoBuildEvent;
class IView;
class GeometryModel;
class RenderableModel;
class ICommand;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние создания отрезка линии
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CreateLineSegmentState : public IState
{
private:
  enum class Status
  {
    AwaitActivate,
    AwaitFirstPos,
    AwaitSecondPos,
    AwaitConfirm
  };

private:
  std::shared_ptr<IView> m_view;
  std::shared_ptr<LineSegment> m_temporarySegment;

  GeometryModel & m_geometry;
  RenderableModel & m_renderable;

  Status m_status;

  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  void CreateTemporaryFigure(const Point & pos);
  void UpdateEndPosTemporaryFigure(const Point & pos);
  void RemoveTemporaryFigure();

  std::unique_ptr<ICommand> OnSceneMousePressEvent(const SceneMouseEvent & mouseEv);
  void OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> OnCompleteDrawingEvent(const CompleteDrawingEvent & ev);
  void OnAutoBuildEvent(const AutoBuildEvent & ev);
  std::unique_ptr<ICommand> CreateDrawCommand(const Point & first, const Point & second);

public:
  CreateLineSegmentState(std::shared_ptr<IView> view, GeometryModel & geometry, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};