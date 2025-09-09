#include <ICommand.h>
#include <IView.h>
#include <DefaultState.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DefaultState::DefaultState(std::shared_ptr<IView> view, GeometryModel & geometryModel)
  : m_view(std::move(view))
  , m_geometry(geometryModel)
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


//
void DefaultState::Activate()
{
  m_view->SetProcessName("Инструмент не выбран");
}


//
void DefaultState::Deactivate()
{
  m_view->SetProcessName("");
}
