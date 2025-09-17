#include <ICommand.h>
#include <MoveFigureCommand.h>
#include <DeleteFigureCommand.h>
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
void DefaultState::OnSceneMousePressEvent(const SceneMouseEvent & event)
{
  if (m_clickedFigure = m_renderable.FindFigure(event.LocalPos(), 2))
    if (m_selectedFigure && m_selectedFigure == m_clickedFigure)
    {
      m_isUserSelected = false;
      m_clickPos = event.LocalPos();
    }
    else
    {
      m_isUserSelected = true;
      Deselect();
      Select(m_clickedFigure);
    }
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
void DefaultState::OnSceneMouseMoveEvent(const SceneMouseEvent& event)
{
  if (m_selectedFigure && m_clickedFigure == m_selectedFigure)
  {
    const Vector delta = event.LocalPos() - m_clickPos;
    if (delta.dx > 5 || delta.dx < -5 || delta.dy > 5 || delta.dy < -5)
    {
      m_isUserWantToMove = true;
      m_selectedFigure->Move(event.LocalPos() - m_selectedFigure->Center());
    }
  };
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие отпускания кнопки мыши
*/
//---
std::unique_ptr<ICommand> DefaultState::OnSceneMouseReleaseEvent(const SceneMouseEvent & event)
{
  if (m_clickedFigure && m_clickedFigure == m_selectedFigure)
  {
    if (m_isUserWantToMove)
    {
      m_isUserWantToMove = false;

      std::shared_ptr<IFigure> fig = std::move(m_clickedFigure);
      m_clickedFigure = nullptr;
      
      fig->Move(m_clickPos - event.LocalPos());
      return std::make_unique<MoveFigureCommand>(fig, event.LocalPos() - m_clickPos);
    }
    else if (!m_isUserSelected)
    {
      Deselect();
    }
    m_clickedFigure = nullptr;
  }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Выделяет объект
*/
//---
void DefaultState::Select(std::shared_ptr<IFigure> figure)
{
  if (!m_selectedFigure)
  {
    m_selectedFigure = std::move(figure);
    m_renderable.SetRenderProperties(m_selectedFigure,
                                     {Color::GREEN(), m_renderable.GetRenderProperties(m_selectedFigure)->style});
  };
}


//------------------------------------------------------------------------------
/**
  Снимает выделение с объекта
*/
//---
void DefaultState::Deselect()
{
  if (m_selectedFigure)
  {
    m_renderable.SetRenderProperties(m_selectedFigure,
                                     {Color::BLACK(), m_renderable.GetRenderProperties(m_selectedFigure)->style});
    m_selectedFigure = nullptr;
  };
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DefaultState::DefaultState(std::shared_ptr<IView> view, RenderableModel & renderableModel)
  : m_view(std::move(view))
  , m_renderable(renderableModel)
  , m_isUserWantToMove(false)
  , m_isUserSelected(false)
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
        OnSceneMousePressEvent(mouseEv);
      else if (event.Type() == EventType::SceneMouseMove)
        OnSceneMouseMoveEvent(mouseEv);
      else
        return OnSceneMouseReleaseEvent(mouseEv);
      break;
    }
    case EventType::SceneDeleteEvent:
    {
      std::shared_ptr<IFigure> fig = m_selectedFigure;
      Deselect();
      return std::make_unique<DeleteFigureCommand>(fig, m_renderable);
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
