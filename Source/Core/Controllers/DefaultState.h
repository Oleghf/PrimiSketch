#pragma once

#include <IState.h>

class IView;
class IFigure;
class SceneMouseEvent;
class RenderableModel;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние приложения по-умолчанию
/**
*/
////////////////////////////////////////////////////////////////////////////////
class DefaultState : public IState
{
private:
  std::shared_ptr<IView> m_view;
  RenderableModel & m_renderable;

private:
  std::unique_ptr<ICommand> OnSceneMousePressEvent(const SceneMouseEvent & event);
  std::unique_ptr<ICommand> OnSceneMouseMoveEvent(const SceneMouseEvent & event);
  std::unique_ptr<ICommand> OnSceneMouseReleaseEvent(const SceneMouseEvent & event);

public:
  DefaultState(std::shared_ptr<IView> view, RenderableModel & renderableModel);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
  void Activate() override;
  void Deactivate() override;
};