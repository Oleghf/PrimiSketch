#pragma once

#include <memory>

#include <IState.h>
#include <Point.h>

class SceneMouseEvent;
class CompleteDrawingEvent;
class IView;
class GeometryModel;
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
  enum class StepCreate
  {
    AwaitActivate,
    AwaitFirstPos,
    AwaitSecondPos,
    AwaitConfirm
  };

private:
  std::shared_ptr<IView> m_view;
  GeometryModel & m_geometry;
  StepCreate m_step;
  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  std::unique_ptr<ICommand> HandleClick(const SceneMouseEvent & mouseEv);
  std::unique_ptr<ICommand> HandleCompleteDrawingEv(const CompleteDrawingEvent & ev);

  std::unique_ptr<ICommand> CompleteDrawing(const Point & first, const Point & second);

public:
  CreateLineSegmentState(std::shared_ptr<IView> view, GeometryModel & geometry);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
  void Activate() override;
  void Deactivate() override;
};