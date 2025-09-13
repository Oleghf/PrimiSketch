#include <IView.h>
#include <Event.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <SceneMouseEvent.h>
#include <LineSegment.h>
#include <CreateFigureCommand.h>
#include <RenderableModel.h>
#include <CreateLineSegmentState.h>


//
void CreateLineSegmentState::CreateTemporaryFigure(const Point& pos)
{
  m_temporarySegment = std::make_shared<LineSegment>(pos, pos);
  m_renderable.SetRenderProperties(m_temporarySegment, {0, 0, 0, 155, m_view->GetStyleLine()});
}


//
void CreateLineSegmentState::UpdateEndPosTemporaryFigure(const Point& pos)
{
  if (m_temporarySegment)
  {
    m_temporarySegment->end = pos;
    m_view->RequestRedraw();
  }
}


//
void CreateLineSegmentState::RemoveTemporaryFigure()
{
  m_renderable.Remove(m_temporarySegment);
  m_temporarySegment = nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::OnSceneMousePressEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMousePress)
  {
    if (m_status == Status::AwaitFirstPos && mouseEv.Button() == MouseButton::Left)
    {
      m_firstPos = mouseEv.LocalPos();
      m_status = Status::AwaitSecondPos;
      CreateTemporaryFigure(m_firstPos);
    }
    else
    {
      m_secondPos = mouseEv.LocalPos();
      if (!m_isAutoBuild)
        m_status = Status::AwaitConfirm;
      else
      {
        m_status = Status::AwaitFirstPos;
        RemoveTemporaryFigure();
        return CreateDrawCommand(m_firstPos, m_secondPos);
      }
    }
  }
  return nullptr;
}


//
std::unique_ptr<ICommand> CreateLineSegmentState::onSceneMouseMoveEvent(const SceneMouseEvent& mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMouseMove)
  {
    if (m_status == Status::AwaitSecondPos && m_status != Status::AwaitConfirm)
        UpdateEndPosTemporaryFigure(mouseEv.LocalPos());
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  if (m_status == Status::AwaitConfirm)
  {
    m_status = Status::AwaitFirstPos;

    RemoveTemporaryFigure();
    if (ev.IsDrawAccepted())
      return CreateDrawCommand(m_firstPos, m_secondPos);
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::CreateDrawCommand(const Point & first, const Point & second)
{
  std::shared_ptr<LineSegment> segment = std::make_shared<LineSegment>(first, second);
  RenderProperties renderableProp{0, 0, 0, 255, m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(segment, renderableProp, m_geometry, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateLineSegmentState::CreateLineSegmentState(std::shared_ptr<IView> view, GeometryModel & geometry,
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
  Обрабатывает событие
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    case EventType::SceneMouseMove:
    {
      const SceneMouseEvent & mouseEvent = static_cast<const SceneMouseEvent &>(event);

      if (event.Type() == EventType::SceneMousePress)
        return OnSceneMousePressEvent(mouseEvent);
      else
        return onSceneMouseMoveEvent(mouseEvent);
    }
    case EventType::CompleteDrawing:
    {
      const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);
      return OnCompleteDrawingEvent(completeDrawEvent);
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
void CreateLineSegmentState::Activate()
{
  m_status = Status::AwaitFirstPos;
  m_view->SetProcessName("Фигура: Отрезок");

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
void CreateLineSegmentState::Deactivate()
{
  m_status = Status::AwaitActivate;
  m_view->SetProcessName("");
}
