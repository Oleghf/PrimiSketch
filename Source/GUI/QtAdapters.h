#pragma once

#include <QMouseEvent>

#include <SceneMouseEvent.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Пространство qt адаптеров
/**
*/
////////////////////////////////////////////////////////////////////////////////
namespace qt_adapters
{
EventType FromQMouseEventType(QMouseEvent * event);
SceneMouseEvent FromQMouseEvent(QMouseEvent * event);
MouseButton FromQtMouseButton(Qt::MouseButton button);

Point FromQPointF(const QPointF & point);
}
