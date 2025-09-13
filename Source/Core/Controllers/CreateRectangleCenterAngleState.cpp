#include <IView.h>
#include <SceneMouseEvent.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <Rectangle.h>
#include <CreateFigureCommand.h>
#include <ICommand.h>
#include <CreateRectangleCenterAngleState.h>


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnSceneMouseEvent(const SceneMouseEvent & mouseEv)
{
  if (m_status == Status::AwaitCenterPos)
  {
    m_status = Status::AwaitAnglePos;
    m_centerPos = mouseEv.LocalPos();
  }
  else
  {
    if (m_isAutoBuild)
    {
      m_status = Status::AwaitCenterPos;
      return CreateDrawCommand(m_centerPos, mouseEv.LocalPos());
    }
    else
    {
      m_status = Status::AwaitConfirm;
      m_anglePos = mouseEv.LocalPos();
    }
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  m_status = Status::AwaitCenterPos;

  if (ev.IsDrawAccepted())
    return CreateDrawCommand(m_centerPos, m_anglePos);
  else
    return nullptr;
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::CreateDrawCommand(const Point & center, const Point & angle)
{
  Point bottomLeft;
  bottomLeft.x = 2 * center.x - angle.x;
  bottomLeft.y = 2 * center.y - angle.y;

  std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(bottomLeft, angle);
  RenderProperties renderableProp{0, 0, 0, 255, m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(rect, renderableProp, m_geometry, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateRectangleCenterAngleState::CreateRectangleCenterAngleState(std::shared_ptr<IView> view, GeometryModel & geometry,
                                                             RenderableModel & renderable)
  : m_view(view)
  , m_geometry(geometry)
  , m_renderable(renderable)
  , m_status(Status::AwaitActivate)
  , m_isAutoBuild(false)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие мыши на сцене
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    {
      const SceneMouseEvent & mouseEvent = static_cast<const SceneMouseEvent &>(event);
      if (mouseEvent.Button() == MouseButton::Left)
        return OnSceneMouseEvent(mouseEvent);
      break;
    }
    case EventType::CompleteDrawing:
    {
      if (m_status == Status::AwaitConfirm)
      {
        const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);
        return OnCompleteDrawingEvent(completeDrawEvent);
      }
      break;
    }
    case EventType::AutoBuild:
    {
      const AutoBuildEvent & autoBuildEv = static_cast<const AutoBuildEvent &>(event);
      m_isAutoBuild = autoBuildEv.IsAutoBuild();
      break;
    }
  }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  \brief Перевести состояние в рабочий режим
  \details Устанавливает название процесса, включает необходимые кнопки в редакторе
*/
//---
void CreateRectangleCenterAngleState::Activate()
{
  m_status = Status::AwaitCenterPos;
  m_view->SetProcessName("Фигура: Прямоугольник по центру и углу");

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, true);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, true);
  m_view->SetActionEnabled(SwitchableEditorAction::AutoBuild, true);
  m_view->SetActionEnabled(SwitchableEditorAction::ChangeStyleLine, true);
}


//------------------------------------------------------------------------------
/**
  \brief Отключить состояние
  \details Устанавливает в качестве названия процесса пустую строку
  \warning Не отключает кнопки редактора
*/
//---
void CreateRectangleCenterAngleState::Deactivate()
{
  m_status = Status::AwaitActivate;
  m_view->SetProcessName("");
}
