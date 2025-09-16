#include <chrono>

#include <ICommand.h>
#include <Event.h>
#include <SceneMouseEvent.h>
#include <IView.h>
#include <SelectedModel.h>
#include <RenderableModel.h>
#include <Vector.h>
#include <DefaultState.h>


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> DefaultState::OnSceneMousePressEvent(const SceneMouseEvent & event)
{
  if (auto fig = m_renderable.FindFigure(event.LocalPos(), 2))
    if (auto selectedFigure = m_selected.FindFigure(event.LocalPos(), 2))
    {
      m_selectedFigure = selectedFigure;
      m_firstPos = event.LocalPos();
    }
    else
    {
      m_selected.Clear();
      m_selected.Add(fig);
      m_renderable.SetRenderProperties(fig, {Color::GREEN(), m_renderable.GetRenderProperties(fig)->style});
    }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
std::unique_ptr<ICommand> DefaultState::OnSceneMouseMoveEvent(const SceneMouseEvent& event)
{
  if (m_selectedFigure)
  {
    Vector delta = event.LocalPos() - m_firstPos;
    if (delta.dx > 5 || delta.dx < -5 || delta.dy > 5 || delta.dy < -5)
    {
      m_isUserWantToMove = true;
      m_selectedFigure->Move(event.LocalPos() - m_selectedFigure->Center());
    }
  };
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие отпускания кнопки мыши
*/
//---
std::unique_ptr<ICommand> DefaultState::OnSceneMouseReleaseEvent(const SceneMouseEvent & event)
{
  if (m_selectedFigure)
  {
    if (m_isUserWantToMove)
    {
      m_isUserWantToMove = false;
      m_selectedFigure = nullptr;
    }
    else
    {
      m_renderable.SetRenderProperties(m_selectedFigure,
                                       {Color::BLACK(), m_renderable.GetRenderProperties(m_selectedFigure)->style});
      m_selected.Clear();
      m_selectedFigure = nullptr;
    }
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DefaultState::DefaultState(std::shared_ptr<IView> view, SelectedModel & selectedModel, RenderableModel & renderableModel)
  : m_view(std::move(view))
  , m_inMoveFigure(nullptr)
  , m_selected(selectedModel)
  , m_renderable(renderableModel)
  , m_isUserWantToMove(false)
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
    case EventType::SceneDeleteEvent:
    {
      auto pred = [this](std::shared_ptr<IFigure> figure)
      {
        m_renderable.Remove(figure);
        return true;
      };
      m_selected.ForEachFigures(pred);
      m_selected.Clear();
      break;
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
