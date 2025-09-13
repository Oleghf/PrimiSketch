#include <BrokenLine.h>
#include <AutoBuildEvent.h>
#include <CompleteDrawingEvent.h>
#include <CreateFigureCommand.h>
#include <CreatePolyLineState.h>
#include <Event.h>
#include <IView.h>
#include <RenderableModel.h>
#include <SceneMouseEvent.h>


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::OnSceneMouseEvent(const SceneMouseEvent & mouseEv)
{
  if (m_status == Status::AwaitPoints)
    m_points.push_back(mouseEv.LocalPos());
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  if (ev.IsDrawAccepted())
    return CreateDrawCommand(m_points);
  return nullptr;
}

  
//------------------------------------------------------------------------------
/**
  Создает команду на создание ломанной по массиву точек
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::CreateDrawCommand(const std::vector<Point> & points)
{
  std::shared_ptr<BrokenLine> polyline = std::make_shared<BrokenLine>(points);
  RenderProperties renderableProp{0, 0, 0, 255, m_view->GetStyleLine()};

  m_points.clear();

  return std::make_unique<CreateFigureCommand>(polyline, renderableProp, m_geometry, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreatePolyLineState::CreatePolyLineState(std::shared_ptr<IView> view, GeometryModel & geometry, RenderableModel & renderable)
  : m_view(view)
  , m_geometry(geometry)
  , m_renderable(renderable)
  , m_status(Status::AwaitActivate)
  , m_isAutoBuild(false)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    {
      const SceneMouseEvent & mouseEv = static_cast<const SceneMouseEvent &>(event);

      if (mouseEv.Button() == MouseButton::Left)
        return OnSceneMouseEvent(mouseEv);
      break;
    }
    case EventType::CompleteDrawing:
    {
      const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);

      return OnCompleteDrawingEvent(completeDrawEvent);
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
void CreatePolyLineState::Activate()
{
  m_status = Status::AwaitPoints;
  m_view->SetProcessName("Фигура: Ломаная");

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, true);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, true);
  m_view->SetActionEnabled(SwitchableEditorAction::AutoBuild, false);
  m_view->SetActionEnabled(SwitchableEditorAction::ChangeStyleLine, true);
}


//------------------------------------------------------------------------------
/**
  \brief Отключить состояние
  \details Устанавливает в качестве названия процесса пустую строку
  \warning Не отключает кнопки редактора
*/
//---
void CreatePolyLineState::Deactivate()
{
  m_status = Status::AwaitActivate;
  m_view->SetProcessName("");
}
