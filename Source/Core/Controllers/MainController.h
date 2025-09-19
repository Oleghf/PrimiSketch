#pragma once

#include <memory>
#include <string>

#include <Tool.h>
#include <PaintController.h>
#include <CommandManager.h>
#include <EventListener.h>
#include <RenderableModel.h>

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
  RenderableModel m_renderableModel;
  PaintController m_paintController;
  
  std::shared_ptr<IView> m_view;

  Tool m_currentTool;
  std::unordered_map <Tool, std::shared_ptr<IState>> m_states;

  double m_scale;

private:
  void Load(const std::string & path);
  void Save(const std::string & path);
  void ExportSVG(const std::string & path);
  void Scale(const Point & anchorPos, double factor);

  void ChangeState(Tool newTool);

public:
  MainController(std::shared_ptr<IView> view);

  void OnEvent(const Event & event) override;
};
