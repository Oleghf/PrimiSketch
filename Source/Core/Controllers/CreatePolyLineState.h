#pragma once

#include <vector>

#include <IState.h>
#include <Point.h>

class LineSegment;
class BrokenLine;
class IView;
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
  ////////////////////////////////////////////////////////////////////////////////
  //
  /// Статус состояния
  /**
  */
  ////////////////////////////////////////////////////////////////////////////////
  enum class Status
  {
    AwaitActivate,  // Ожидает активации
    AwaitFirstPos,  // Ожидает первую точку
    AwaitPoints     // Ожидает остальные точки
  };

private:
  std::shared_ptr<IView> m_view;
  std::vector<std::shared_ptr<LineSegment>> m_temporarySegments;
  std::vector<Point> m_points;

  RenderableModel & m_renderable;

  Status m_status;

  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  void CreateTemporaryFigure(const Point & pos);
  void UpdateEndPosTemporaryFigure(const Point & end);
  void RemoveTemporaryFigure();
  void CreateNewPhantomSegment(const Point & start, const Point & end);

  std::unique_ptr<ICommand> OnSceneMousePressEvent(const SceneMouseEvent & mouseEv);
  void OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> OnCompleteDrawingEvent(const CompleteDrawingEvent & ev);
  std::unique_ptr<ICommand> CreateDrawCommand(const std::vector<Point> & points);

public:
  CreatePolyLineState(std::shared_ptr<IView> view, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};