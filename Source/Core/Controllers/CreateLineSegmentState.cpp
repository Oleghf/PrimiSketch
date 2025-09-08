#include <Event.h>
#include <LineSegment.h>
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
{
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
	    }
		else
		{
          m_step = StepCreate::AwaitFirstPos;

          std::shared_ptr<LineSegment> segment = std::make_shared<LineSegment>(m_firstPos, mouseEv.LocalPos());
          return std::make_unique<CreateFigureCommand>(segment, m_geometry);
		}

		break;
	}
    }

	return nullptr;
}
