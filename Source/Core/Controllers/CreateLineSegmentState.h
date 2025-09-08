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
    AwaitSecondPos
  };

private:
  GeometryModel & m_geometry;
  StepCreate m_step;
  Point m_firstPos;

public:
  CreateLineSegmentState(GeometryModel & geometry);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
};