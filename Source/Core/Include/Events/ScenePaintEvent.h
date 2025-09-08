#pragma once


#include <Event.h>
#include <PrimitiveView.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Событие перерисовки сцены
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ScenePaintEvent : public Event
{
private:
  PrimitiveView & m_primitiveView;

public:
  ScenePaintEvent(PrimitiveView & view)
    : m_primitiveView(view)
  {
  }
  
  EventType Type() const override { return EventType::PaintEvent; }

  PrimitiveView & PrimitiveView() const { return m_primitiveView; }
};
