#pragma once

#include <memory>
#include <string>

#include <Tools.h>
#include <StyleLine.h>
#include <PaintController.h>
#include <CommandManager.h>
#include <EventListener.h>
#include <GeometryModel.h>
#include <RenderableModel.h>
#include <RenderableProperties.h>

class IState;
class IView;

////////////////////////////////////////////////////////////////////////////////
//
/// Контроллер приложения
/**
*/
////////////////////////////////////////////////////////////////////////////////
class MainController : public EventListener
{
private:
  CommandManager m_commandManager;
  GeometryModel m_geometryModel;
  RenderableModel m_renderableModel;
  PaintController m_paintController;
  
  std::shared_ptr<IView> m_view;
  std::shared_ptr<IState> m_currentState;

  std::unordered_map <Tool, std::shared_ptr<IState>> m_states;

private:
  void ChangeState(Tool newTool);

public:
  MainController(std::shared_ptr<IView> view);

  void OnEvent(const Event & event) override;
};
