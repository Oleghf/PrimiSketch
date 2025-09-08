#pragma once

#include <memory>

#include <IState.h>
#include <Point.h>

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
    AwaitFirstPos,
    AwaitSecondPos,
    AwaitConfirm
  };

private:
  GeometryModel & m_geometry;
  StepCreate m_step;
  Point m_firstPos;
  Point m_secondPos;

  bool m_isAutoBuild;

private:
  std::unique_ptr<ICommand> CompleteDrawing(const Point & first, const Point & second);

public:
  CreateLineSegmentState(GeometryModel & geometry);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
};