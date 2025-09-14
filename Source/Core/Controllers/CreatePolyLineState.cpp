#include <BrokenLine.h>
#include <LineSegment.h>
#include <Event.h>
#include <AutoBuildEvent.h>
#include <CompleteDrawingEvent.h>
#include <SceneMouseEvent.h>
#include <CreateFigureCommand.h>
#include <IView.h>
#include <RenderableModel.h>
#include <CreatePolyLineState.h>


//------------------------------------------------------------------------------
/**
  Создает временную(фантомную) фигуру по переданной координате(в виде точки)
*/
//---
void CreatePolyLineState::CreateTemporaryFigure(const Point & pos)
{
  Color color = Color::BLACK();
  color.a = 155;

  m_temporarySegments.push_back(std::make_shared<LineSegment>(pos, pos));
  m_renderable.SetRenderProperties(m_temporarySegments.back(), {color, m_view->GetStyleLine()});
}


//------------------------------------------------------------------------------
/**
  Обновляет конечную точку временной(фантомной) фигуры, если такая была создана
*/
//---
void CreatePolyLineState::UpdateEndPosTemporaryFigure(const Point & end)
{
  if (!m_temporarySegments.empty())
  {
    m_temporarySegments.back()->end = end;
    m_view->RequestRedraw();
  }
}


//------------------------------------------------------------------------------
/**
  Создает новый фантомный сегмент ломанной
*/
//---
void CreatePolyLineState::CreateNewPhantomSegment(const Point& start, const Point& end)
{
  Color color = Color::BLACK();
  color.a = 155;

  std::shared_ptr<LineSegment> segment = std::make_shared<LineSegment>(start, end);
  m_temporarySegments.push_back(segment);
  m_renderable.SetRenderProperties(segment, {color, m_view->GetStyleLine()});
}


//------------------------------------------------------------------------------
/**
  Удаляет временную(фантомную) фигуру
*/
//---
void CreatePolyLineState::RemoveTemporaryFigure()
{
  for (auto & segment : m_temporarySegments)
    m_renderable.Remove(segment);
  m_temporarySegments.clear();
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::OnSceneMousePressEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMousePress && mouseEv.Button() == MouseButton::Left)
    if (m_status == Status::AwaitFirstPos)
    {
      m_firstPos = mouseEv.LocalPos();
      m_status = Status::AwaitPoints;
      CreateTemporaryFigure(m_firstPos);
    }
    else
    {
      m_secondPos = mouseEv.LocalPos();
      CreateNewPhantomSegment(m_secondPos, m_firstPos);
      m_points.push_back(m_firstPos);
      m_points.push_back(m_secondPos);
      m_firstPos = m_points.back();
    }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
void CreatePolyLineState::OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMouseMove)
    if (m_status != Status::AwaitFirstPos)
      UpdateEndPosTemporaryFigure(mouseEv.LocalPos());
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreatePolyLineState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  if (m_status == Status::AwaitPoints)
  {
    m_status = Status::AwaitFirstPos;

    RemoveTemporaryFigure();
    std::vector<Point> points = std::move(m_points);
    m_points.clear();

    if (ev.IsDrawAccepted())
      return CreateDrawCommand(points);
  }
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
  RenderProperties renderableProp{Color::BLACK(), m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(polyline, renderableProp, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreatePolyLineState::CreatePolyLineState(std::shared_ptr<IView> view, RenderableModel & renderable)
  : m_view(std::move(view))
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
  m_status = Status::AwaitFirstPos;
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
  RemoveTemporaryFigure();
  m_view->SetProcessName("");
}
