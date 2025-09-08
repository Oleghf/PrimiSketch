#pragma once

#include <Event.h>

#include <Tools.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Событие смены инструмента
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ToolChangeEvent : public Event
{
private:
  Tool m_tool;

public:
    ToolChangeEvent(Tool type)
        : m_tool(type)
    {
    }
    EventType Type() const override { return EventType::ToolChange; }
    Tool Tool() const { return m_tool; }
};