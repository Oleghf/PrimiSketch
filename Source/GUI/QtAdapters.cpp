#include <QMouseEvent>

#include <QtAdapters.h>


//------------------------------------------------------------------------------
/**
  Приводит qt тип события мыши в тип приложения
*/
//---
EventType qt_adapters::FromQMouseEventType(QMouseEvent * event)
{
  switch (event->type())
  {
    case QEvent::Type::MouseButtonRelease:
      return EventType::SceneMouseRelease;
    case QEvent::Type::MouseMove:
      return EventType::SceneMouseMove;
    default:
      return EventType::SceneMousePress;
  }
}


//------------------------------------------------------------------------------
/**
  Приводит qt событие мыши в событие мыши приложения
*/
//---
SceneMouseEvent qt_adapters::FromQMouseEvent(QMouseEvent* event)
{
  EventType type = FromQMouseEventType(event);
  Point localPos = FromQPointF(event->localPos());
  MouseButton button = FromQtMouseButton(event->button());

  SceneMouseEvent mouseEv(type, localPos, button);
  return mouseEv;
}


//------------------------------------------------------------------------------
/**
  Приводит qt кнопку мыши в кнопку приложения
*/
//---
MouseButton qt_adapters::FromQtMouseButton(Qt::MouseButton button)
{
  switch (button)
  {
    case Qt::LeftButton:
      return MouseButton::Left;
    case Qt::MiddleButton:
      return MouseButton::Middle;
    case Qt::RightButton:
      return MouseButton::Right;
    default:
      return MouseButton::Unknow;
  }
}


//------------------------------------------------------------------------------
/**
  Приводит qt точку в точку приложения
*/
//---
Point qt_adapters::FromQPointF(const QPointF & point)
{
  return {point.x(), point.y()};
}
