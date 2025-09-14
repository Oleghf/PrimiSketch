#pragma once

#include <vector>

#include <IState.h>
#include <Point.h>

class LineSegment;
class BrokenLine;
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
    AwaitFirstPos,
    AwaitPoints
  };

private:
  std::shared_ptr<IView> m_view;
  std::vector<std::shared_ptr<LineSegment>> m_temporarySegments;

  GeometryModel & m_geometry;
  RenderableModel & m_renderable;

  Status m_status;

  std::vector<Point> m_points;
  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  void CreateTemporaryFigure(const Point & pos);
  void UpdateEndPosTemporaryFigure(const Point & end);
  void RemoveTemporaryFigure();
  void CreateNewLineSegment(const Point & start, const Point & end);

  std::unique_ptr<ICommand> OnSceneMousePressEvent(const SceneMouseEvent & mouseEv);
  void OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> OnCompleteDrawingEvent(const CompleteDrawingEvent & ev);
  std::unique_ptr<ICommand> CreateDrawCommand(const std::vector<Point> & points);

public:
  CreatePolyLineState(std::shared_ptr<IView> view, GeometryModel & geometry, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};