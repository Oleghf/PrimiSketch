#pragma once

#include <Event.h>
#include <Point.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Перечисление кнопок мыши
/**
*/
////////////////////////////////////////////////////////////////////////////////
enum class MouseButton
{
	Left,
	Middle, 
	Right,
	Unknow
};


////////////////////////////////////////////////////////////////////////////////
//
/// Событие мыши на сцене
/**
*/
////////////////////////////////////////////////////////////////////////////////
class SceneMouseEvent : public Event
{
private:
  EventType m_eventType;
  Point m_localPos;
  MouseButton m_button;

public:
  SceneMouseEvent(EventType type, const Point & localPos, MouseButton button);

  EventType Type() const override { return m_eventType; }

  Point LocalPos() const { return m_localPos; }

  MouseButton Button() const {return m_button;}
};