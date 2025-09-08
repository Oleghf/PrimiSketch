#pragma once

#include <memory>
#include <string>

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
  CommandManager m_commandManager;
  GeometryModel m_geometryModel;
  
  std::shared_ptr<IState> m_state;
  std::shared_ptr<IView> m_view;

public:
  MainController(std::shared_ptr<IView> view);

  void OnEvent(const Event & event) override;

  void SaveAs(const std::string & title, const std::string & path);
  void Load(const std::string & title, const std::string & path);
};
