#pragma once

#include <Event.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Событие изменения состояния авто построения
/**
*/
////////////////////////////////////////////////////////////////////////////////
class AutoBuildEvent : public Event
{
  bool m_isAutoBuild;

public:
  AutoBuildEvent(bool isAutoBuildOn)
    : m_isAutoBuild(isAutoBuildOn)
  {
  }
  EventType Type() const override { return EventType::AutoBuild; }
  bool IsAutoBuild() const { return m_isAutoBuild; }
};