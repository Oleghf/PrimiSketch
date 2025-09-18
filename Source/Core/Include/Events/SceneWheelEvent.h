#pragma once

#include <Event.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Событие колесика на сцене
/**
*/
////////////////////////////////////////////////////////////////////////////////
class SceneWheelEvent : public Event
{
private:
  double m_degrees;
  Point m_cursorPos;

public:
  SceneWheelEvent(double degrees, const Point & cursorPos)
    : m_degrees(degrees)
    , m_cursorPos(cursorPos)
  {
  }

  EventType Type() const override { return EventType::SceneWheelEvent; }

  double Degrees() const { return m_degrees; }
  Point CursorPos() const { return m_cursorPos; }
};
