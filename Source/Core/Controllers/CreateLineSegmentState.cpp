#include <IView.h>
#include <Event.h>
#include <LineSegment.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <SceneMouseEvent.h>
#include <CreateFigureCommand.h>
#include <CreateLineSegmentState.h>


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::HandleClick(const SceneMouseEvent & mouseEv)
{
  if (m_step == StepCreate::AwaitFirstPos)
  {
    m_step = StepCreate::AwaitSecondPos;
    m_firstPos = mouseEv.LocalPos();
    return nullptr;
  }
  else
  {
    if (m_isAutoBuild)
    {
      m_step = StepCreate::AwaitFirstPos;
      return CompleteDrawing(m_firstPos, mouseEv.LocalPos());
    }
    else
    {
      m_step = StepCreate::AwaitConfirm;
      m_secondPos = mouseEv.LocalPos();
      return nullptr;
    }
  }
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::HandleCompleteDrawingEv(const CompleteDrawingEvent& ev)
{
  if (ev.IsAccepted())
  {
    m_step = StepCreate::AwaitFirstPos;
    return CompleteDrawing(m_firstPos, m_secondPos);
  }
  else
  {
    m_step = StepCreate::AwaitFirstPos;
    return nullptr;
  }
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateLineSegmentState::CreateLineSegmentState(std::shared_ptr<IView> view, GeometryModel & geometry)
  : m_view(view)
  , m_geometry(geometry)
  , m_step(StepCreate::AwaitFirstPos)
  , m_isAutoBuild(false)
{
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::CompleteDrawing(const Point & first, const Point & second)
{
  std::shared_ptr<LineSegment> segment = std::make_shared<LineSegment>(first, second);
  return std::make_unique<CreateFigureCommand>(segment, m_geometry);
}


//------------------------------------------------------------------------------
/**
  \brief Обрабатывает события мыши по сцене
  \details При получении первого события нажатия мыши по сцене запоминает координаты нажатия.
  При получении второго события нажатия мыши  по сцене создает команду создания отрезка и возвращает ее.
*/
//---
std::unique_ptr<ICommand> CreateLineSegmentState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    {
      const SceneMouseEvent & mouseEv = static_cast<const SceneMouseEvent &>(event);
      if (mouseEv.Button() != MouseButton::Left)
        break;

      return HandleClick(mouseEv);
    }
    case EventType::CompleteDrawing:
    {
      if (m_step != StepCreate::AwaitConfirm)
        break;
      const CompleteDrawingEvent & comDrEv = static_cast<const CompleteDrawingEvent &>(event);

      return HandleCompleteDrawingEv(comDrEv);
    }
    case EventType::AutoBuild:
    {
      const AutoBuildEvent & autoBuildEv = static_cast<const AutoBuildEvent &>(event);
      m_isAutoBuild = autoBuildEv.IsAutoBuild();
      return nullptr;
    }
  }

	return nullptr;
}


//
void CreateLineSegmentState::Activate()
{
  m_step = StepCreate::AwaitFirstPos;
  m_view->SetProcessName("Фигура: Отрезок");
}


//
void CreateLineSegmentState::Deactivate()
{
  m_step = StepCreate::AwaitActivate;
  m_view->SetProcessName("");
}
