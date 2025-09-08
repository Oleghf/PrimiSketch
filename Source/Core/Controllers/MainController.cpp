#include <IView.h>
#include <IState.h>
#include <Event.h>
#include <MainController.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
MainController::MainController(std::shared_ptr<IView> view): m_view(view)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
void MainController::OnEvent(const Event& event)
{
	// ... WIP
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
