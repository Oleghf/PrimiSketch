#pragma once

#include <IState.h>

class IView;
class IFigure;
class SceneMouseEvent;
class SelectedModel;
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
  std::shared_ptr<IFigure> m_inMoveFigure;
  std::shared_ptr<IFigure> m_selectedFigure;

  SelectedModel & m_selected;
  RenderableModel & m_renderable;

  Point m_firstPos;
  bool m_isUserWantToMove;

private:
  std::unique_ptr<ICommand> OnSceneMousePressEvent(const SceneMouseEvent & event);
  std::unique_ptr<ICommand> OnSceneMouseMoveEvent(const SceneMouseEvent & event);
  std::unique_ptr<ICommand> OnSceneMouseReleaseEvent(const SceneMouseEvent & event);

public:
  DefaultState(std::shared_ptr<IView> view, SelectedModel & selectedModel, RenderableModel & renderableModel);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
  void Activate() override;
  void Deactivate() override;
};