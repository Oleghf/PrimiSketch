#pragma once

#include <memory>

#include <IState.h>
#include <Point.h>

class SceneMouseEvent;
class CompleteDrawingEvent;
class IView;
class GeometryModel;
class RenderableModel;
class ICommand;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние создания прямоугольника по двум точкам
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CreateRectangleTwoPointsState : public IState
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

  GeometryModel & m_geometry;
  RenderableModel & m_renderable;

  Status m_status;

  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  std::unique_ptr<ICommand> OnSceneMouseEvent(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> OnCompleteDrawingEvent(const CompleteDrawingEvent & ev);

  std::unique_ptr<ICommand> CreateDrawCommand(const Point & first, const Point & second);

public:
  CreateRectangleTwoPointsState(std::shared_ptr<IView> view, GeometryModel & geometry, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};
