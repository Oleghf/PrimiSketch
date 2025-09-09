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
    switch (newTool)
    {
      case Tool::None:
      {
        m_view->SetProcessName("Инструмент не выбран");
        m_currentState = m_states[Tool::None];
        break;
      }
      case Tool::LineSegment:
      {
        m_view->SetProcessName("Фигура: Отрезок");
        m_currentState = m_states[Tool::LineSegment];
        break;
      }
      // ...WIP
    }
}


//------------------------------------------------------------------------------
/**
  Запрашивает диалог сохранения текущего состояния программы
*/
//---
void MainController::SaveAs(const std::string & title, const std::string & path)
{
  m_view->OpenSaveFileDialog(title, path); // ... WIP
}


//------------------------------------------------------------------------------
/**
  Запрашивает диалог загрузки текущего состояния программы
*/
//---
void MainController::Load(const std::string & title, const std::string & path)
{
  m_view->OpenLoadFileDialog(title, path); // ... WIP
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
MainController::MainController(std::shared_ptr<IView> view)
  : m_view(view)
  , m_currentState(std::make_shared<DefaultState>(m_geometryModel))
  , m_paintController(view, m_geometryModel)
{
  m_states[Tool::None] = m_currentState;
  m_states[Tool::LineSegment] = std::make_shared<CreateLineSegmentState>(m_geometryModel);

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
      SaveAs("Сохранение", "");
      break;
	}
    case EventType::LoadFile:
    {
      Load("Загрузка", "");
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