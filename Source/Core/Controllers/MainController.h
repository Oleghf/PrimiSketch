#pragma once

#include <memory>
#include <string>

#include <Tools.h>
#include <StyleLine.h>
#include <PaintController.h>
#include <CommandManager.h>
#include <EventListener.h>
#include <GeometryModel.h>

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
	struct RenderableProperties
	{
    int r, g, b;
    StyleLine style;
	};
private:
  CommandManager m_commandManager;
  GeometryModel m_geometryModel;
  PaintController m_paintController;
  
  std::shared_ptr<IView> m_view;
  std::shared_ptr<IState> m_currentState;

  std::unordered_map <Tool, std::shared_ptr<IState>> m_states;
  std::unordered_map<std::shared_ptr<IFigure>, RenderableProperties> m_renderableProperties;

private:
  void ChangeState(Tool newTool);

public:
  MainController(std::shared_ptr<IView> view);

  void OnEvent(const Event & event) override;
};
