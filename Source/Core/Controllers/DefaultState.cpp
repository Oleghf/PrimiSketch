#include <ICommand.h>
#include <Event.h>
#include <SceneMouseEvent.h>
#include <IView.h>
#include <GeometryModel.h>
#include <RenderableModel.h>
#include <Vector.h>
#include <DefaultState.h>


//
std::unique_ptr<ICommand> DefaultState::OnSceneMousePressEvent(const SceneMouseEvent & event)
{
  return nullptr;
}


//
std::unique_ptr<ICommand> DefaultState::OnSceneMouseMoveEvent(const SceneMouseEvent& event)
{
  return nullptr;
}


//
std::unique_ptr<ICommand> DefaultState::OnSceneMouseReleaseEvent(const SceneMouseEvent & event)
{
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DefaultState::DefaultState(std::shared_ptr<IView> view, RenderableModel & renderableModel)
  : m_view(std::move(view))
  , m_renderable(renderableModel)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
std::unique_ptr<ICommand> DefaultState::OnEvent(const Event& event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    case EventType::SceneMouseMove:
    case EventType::SceneMouseRelease:
    {
      const SceneMouseEvent & mouseEv = static_cast<const SceneMouseEvent &>(event);
      if (event.Type() == EventType::SceneMousePress)
        return OnSceneMousePressEvent(mouseEv);
      else if (event.Type() == EventType::SceneMouseMove)
        return OnSceneMouseMoveEvent(mouseEv);
      else
        return OnSceneMouseReleaseEvent(mouseEv);
    }
  }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Активировать состояние
*/
//---
void DefaultState::Activate()
{
  m_view->SetProcessName("Инструмент не выбран");

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, false);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, false);
  m_view->SetActionEnabled(SwitchableEditorAction::AutoBuild, false);
  m_view->SetActionEnabled(SwitchableEditorAction::ChangeStyleLine, false);
}


//------------------------------------------------------------------------------
/**
  Деактивировать состояние
*/
//---
void DefaultState::Deactivate()
{
  m_view->SetProcessName("");
}
