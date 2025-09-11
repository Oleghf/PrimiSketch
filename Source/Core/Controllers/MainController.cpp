#include <ScenePaintEvent.h>
#include <IView.h>
#include <IState.h>
#include <CreateLineSegmentState.h>
#include <DefaultState.h>
#include <Event.h>
#include <ToolChangeEvent.h>
#include <ICommand.h>
#include <MainController.h>


//
void MainController::ChangeState(Tool newTool)
{
  m_currentState->Deactivate();
  m_states[newTool]->Activate();
  m_currentState = m_states[newTool];
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
MainController::MainController(std::shared_ptr<IView> view)
  : m_view(view)
  , m_currentState(std::make_shared<DefaultState>(m_view, m_geometryModel))
  , m_paintController(view, m_renderableModel)
{
  m_states[Tool::None] = m_currentState;
  m_states[Tool::LineSegment] = std::make_shared<CreateLineSegmentState>(m_view, m_geometryModel, m_renderableModel);

  ChangeState(Tool::None);
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
void MainController::OnEvent(const Event& event)
{
	switch (event.Type())
	{
    case EventType::SaveFile:
	{
      m_view->OpenSaveFileDialog("Сохранение", "");
      break;
	}
    case EventType::LoadFile:
    {
      m_view->OpenLoadFileDialog("Загрузка", "");
      break;
    }
    case EventType::Undo:
    {
      m_commandManager.Undo();
      break;
    }
    case EventType::Redo:
    {
      m_commandManager.Redo();
      break;
    }
    case EventType::PaintEvent:
    {
      m_paintController.OnPaintEvent(static_cast<const ScenePaintEvent &>(event));
      break;
    }
    case EventType::ToolChange:
    {
      ToolChangeEvent tcEv = static_cast<const ToolChangeEvent &>(event);
      ChangeState(tcEv.Tool());
      break;
    }
    default:
    {
      m_commandManager.Execute(m_currentState->OnEvent(event));
      break;
    }
    }
}