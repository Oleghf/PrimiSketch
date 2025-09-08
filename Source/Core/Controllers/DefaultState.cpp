#include <ICommand.h>

#include <DefaultState.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DefaultState::DefaultState(GeometryModel& geometryModel) : m_geometry(geometryModel)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
std::unique_ptr<ICommand> DefaultState::OnEvent(const Event& event)
{
  return nullptr; // ... WIP
}
