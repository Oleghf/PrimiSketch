#pragma once

#include <Event.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Событие завершения рисования
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CompleteDrawingEvent : public Event
{
private:
  bool m_isAccepted;

public:
  CompleteDrawingEvent(bool isAccepted)
    : m_isAccepted(isAccepted)
  {
  }

  EventType Type() const override { return EventType::CompleteDrawing; }
  bool IsAccepted() const { return m_isAccepted; }
};
