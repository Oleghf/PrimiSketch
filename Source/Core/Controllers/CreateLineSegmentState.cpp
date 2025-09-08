#include <Event.h>
#include <LineSegment.h>
#include <CompleteDrawingEvent.h>
#include <SceneMouseEvent.h>
#include <CreateFigureCommand.h>
#include <CreateLineSegmentState.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateLineSegmentState::CreateLineSegmentState(GeometryModel & geometry)
  : m_geometry(geometry)
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
        }
      }

      break;
    }
    case EventType::CompleteDrawing:
    {
      if (m_step != StepCreate::AwaitConfirm)
        break;

      const CompleteDrawingEvent & comDrEvEv = static_cast<const CompleteDrawingEvent &>(event);
      if (comDrEvEv.IsAccepted())
      {
        m_step = StepCreate::AwaitFirstPos;
        return CompleteDrawing(m_firstPos, m_secondPos);
      }
      else
      {
        m_step = StepCreate::AwaitFirstPos;
      }
    }
  }

	return nullptr;
}
