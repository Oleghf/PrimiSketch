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
  std::shared_ptr<IFigure> m_selectedFigure;
  std::shared_ptr<IFigure> m_clickedFigure;

  RenderableModel & m_renderable;

  Point m_clickPos;
  bool m_isUserWantToMove;
  bool m_isUserSelected;

private:
  void OnSceneMousePressEvent(const SceneMouseEvent & event);
  void OnSceneMouseMoveEvent(const SceneMouseEvent & event);
  std::unique_ptr<ICommand> OnSceneMouseReleaseEvent(const SceneMouseEvent & event);

  void Select(std::shared_ptr<IFigure> figure);
  void Deselect();

public:
  DefaultState(std::shared_ptr<IView> view, RenderableModel & renderableModel);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
  void Activate() override;
  void Deactivate() override;
};