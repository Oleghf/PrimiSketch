#include <IView.h>
#include <Event.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <SceneMouseEvent.h>
#include <CreateFigureCommand.h>
#include <RenderableModel.h>
#include <LineSegment.h>
#include <CreateLineSegmentState.h>


//------------------------------------------------------------------------------
/**
  Создает временную(фантомную) фигуру по переданной координате(в виде точки)
*/
//---
void CreateLineSegmentState::CreateTemporaryFigure(const Point& pos)
{
  Color color = Color::BLACK();
  color.a = 155;
  m_temporarySegment = std::make_shared<LineSegment>(pos, pos);
  m_renderable.SetRenderProperties(m_temporarySegment, {color, m_view->GetStyleLine()});
}


//------------------------------------------------------------------------------
/**
  Обновляет конечную точку временной(фантомной) фигуры, если такая была создана
*/
//---
void CreateLineSegmentState::UpdateEndPosTemporaryFigure(const Point& pos)
{
  if (m_temporarySegment)
  {
    m_temporarySegment->end = pos;
    m_view->RequestRedraw();
  }
}


//------------------------------------------------------------------------------
/**
  Удаляет временную(фантомную) фигуру
*/
//---
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
  if (mouseEv.Type() == EventType::SceneMousePress && mouseEv.Button() == MouseButton::Left)
    if (m_status == Status::AwaitFirstPos)
    {
      m_firstPos = mouseEv.LocalPos();
      m_status = Status::AwaitSecondPos;
      CreateTemporaryFigure(m_firstPos);
    }
    else if (m_status != Status::AwaitConfirm)
    {
      m_secondPos = mouseEv.LocalPos();
      if (m_isAutoBuild)
      {
        m_status = Status::AwaitFirstPos;
        RemoveTemporaryFigure();
        return CreateDrawCommand(m_firstPos, m_secondPos);
      }
      else
        m_status = Status::AwaitConfirm;
    }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
void CreateLineSegmentState::OnSceneMouseMoveEvent(const SceneMouseEvent& mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMouseMove)
    if (m_status == Status::AwaitSecondPos && m_status != Status::AwaitConfirm)
        UpdateEndPosTemporaryFigure(mouseEv.LocalPos());
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
  Обрабатывает событие изменения галочки "Автоматическое построение"
*/
//---
void CreateLineSegmentState::OnAutoBuildEvent(const AutoBuildEvent& ev)
{
  m_isAutoBuild = ev.IsAutoBuild();

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, !m_isAutoBuild);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, !m_isAutoBuild);
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::CreateDrawCommand(const Point & first, const Point & second)
{
  std::shared_ptr<LineSegment> segment = std::make_shared<LineSegment>(first, second);
  RenderProperties renderableProp{Color::BLACK(), m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(segment, renderableProp, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateLineSegmentState::CreateLineSegmentState(std::shared_ptr<IView> view,
                                               RenderableModel & renderable)
  : m_view(view)
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
      OnSceneMouseMoveEvent(mouseEvent);
      break;
    }
    case EventType::CompleteDrawing:
    {
      const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);
      return OnCompleteDrawingEvent(completeDrawEvent);
    }
    case EventType::AutoBuild:
    {
      const AutoBuildEvent & autoBuildEv = static_cast<const AutoBuildEvent &>(event);
      OnAutoBuildEvent(autoBuildEv);
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
  RemoveTemporaryFigure();
  m_view->SetProcessName("");
}
