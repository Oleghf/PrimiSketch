#include <IView.h>
#include <SceneMouseEvent.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <Rectangle.h>
#include <CreateFigureCommand.h>
#include <ICommand.h>
#include <CreateRectangleTwoPointsState.h>


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnSceneMouseEvent(const SceneMouseEvent & mouseEv)
{
  if (m_status == Status::AwaitFirstPos)
  {
    m_status = Status::AwaitSecondPos;
    m_firstPos = mouseEv.LocalPos();
  }
  else
  {
    if (m_isAutoBuild)
    {
      m_status = Status::AwaitFirstPos;
      return CreateDrawCommand(m_firstPos, mouseEv.LocalPos());
    }
    else
    {
      m_status = Status::AwaitConfirm;
      m_secondPos = mouseEv.LocalPos();
    }
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  m_status = Status::AwaitFirstPos;

  if (ev.IsDrawAccepted())
    return CreateDrawCommand(m_firstPos, m_secondPos);
  else
    return nullptr;
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::CreateDrawCommand(const Point & first, const Point & second)
{
  std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(first, second);
  RenderableProperties renderableProp{0, 0, 0, 255, m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(rect, renderableProp, m_geometry, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateRectangleTwoPointsState::CreateRectangleTwoPointsState(std::shared_ptr<IView> view, GeometryModel & geometry,
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
  \brief Обрабатывает события мыши по сцене
  \details При получении первого события нажатия мыши по сцене запоминает координаты нажатия.
  При получении второго события нажатия мыши  по сцене создает команду создания отрезка и возвращает ее.
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnEvent(const Event & event)
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
void CreateRectangleTwoPointsState::Activate()
{
  m_status = Status::AwaitFirstPos;
  m_view->SetProcessName("Фигура: Прямоугольник по двум точкам");

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
void CreateRectangleTwoPointsState::Deactivate()
{
  m_status = Status::AwaitActivate;
  m_view->SetProcessName("");
}
