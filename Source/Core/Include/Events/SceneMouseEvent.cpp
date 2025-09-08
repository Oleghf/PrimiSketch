#include <cassert>

#include <SceneMouseEvent.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
SceneMouseEvent::SceneMouseEvent(EventType type, const Point& localPos, MouseButton button)
	: m_eventType(type)
	, m_localPos(localPos)
	, m_button(button)
{
  assert(type == EventType::SceneMousePress || type == EventType::SceneMouseMove || type == EventType::SceneMouseRelease);
}
