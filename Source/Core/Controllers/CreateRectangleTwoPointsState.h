#pragma once

#include <memory>

#include <IState.h>
#include <Point.h>

class Rectangle;
class SceneMouseEvent;
class CompleteDrawingEvent;
class IView;
class RenderableModel;
class ICommand;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние создания прямоугольника по двум точкам(крайним)
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CreateRectangleTwoPointsState : public IState
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
    AwaitSecondPos, // Ожидает вторую точку
    AwaitConfirm    // Ожидает подтверждение введеных данных
  };

private:
  std::shared_ptr<IView> m_view;
  std::shared_ptr<Rectangle> m_temporaryRectangle;

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
  CreateRectangleTwoPointsState(std::shared_ptr<IView> view, RenderableModel & renderable);

  std::unique_ptr<ICommand> OnEvent(const Event & event) override;

  void Activate() override;
  void Deactivate() override;
};
