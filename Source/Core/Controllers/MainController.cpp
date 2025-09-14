#include <Event.h>
#include <ScenePaintEvent.h>
#include <ToolChangeEvent.h>
#include <IState.h>
#include <DefaultState.h>
#include <CreateLineSegmentState.h>
#include <CreateRectangleCenterAngleState.h>
#include <CreatePolyLineState.h>
#include <CreateRectangleTwoPointsState.h>
#include <ICommand.h>
#include <IView.h>
#include <MainController.h>


//------------------------------------------------------------------------------
/**
  Сохранить состояние программы в файл
*/
//---
void MainController::Save(const std::string & path)
{
}


//------------------------------------------------------------------------------
/**
  Загрузить состояние программы из файла
*/
//---
void MainController::Load(const std::string& path)
{
}


//------------------------------------------------------------------------------
/**
  Изменить состояние приложения
*/
//---
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
  , m_currentState(std::make_shared<DefaultState>(m_view, m_renderableModel))
  , m_paintController(view, m_renderableModel)
{
  m_states[Tool::None] = m_currentState;
  m_states[Tool::LineSegment] = std::make_shared<CreateLineSegmentState>(m_view, m_renderableModel);
  m_states[Tool::BrokenLine] = std::make_shared<CreatePolyLineState>(m_view, m_renderableModel);
  m_states[Tool::RectangleTwoPoints] = std::make_shared<CreateRectangleTwoPointsState>(m_view, m_renderableModel);
  m_states[Tool::RectangleCenterAngle] = std::make_shared<CreateRectangleCenterAngleState>(m_view, m_renderableModel);

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