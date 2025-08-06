#pragma once


#include <QMainWindow>

#include <IView.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Qt представление
/**
*/
////////////////////////////////////////////////////////////////////////////////
class QtView : public QMainWindow, public IView
{
	Q_OBJECT
private:
  // Слушатели
  std::vector<std::shared_ptr<EventListener>> m_listeners;

  // Действия в редакторе
  QAction * m_loadAs;
  QAction * m_saveAs;
  QAction * m_undo;
  QAction * m_redo;

  // Коэффициент масштабирования
  double m_zoomFactor;

 private:
  void setupMenu();
  void setupToolBar();

public:
  QtView();

  void RequestRedraw() override {};

  void SetActionEnabled(EditorAction action, bool isEnabled) override {};
  bool IsActionEnabled(EditorAction action) override { return true; };

  void SetProcessName(const std::string & string) override {};
  std::string ProccessName() const override { return ""; };

  std::string OpenSaveFileDialog(const std::string & title, const std::string & initPath) override { return ""; };
  std::string OpenLoadFileDialog(const std::string & title, const std::string & initPath) override { return ""; };
  void ShowMessage(const std::string & title, const std::string & message, MessageType type) override {};

  void SetZoomFactor(double factor) override {};
  double ZoomFactor() const override { return 1.0; };

  void AddEventListener(std::shared_ptr<EventListener> listener) override {};
  void RemoveEventListener(std::shared_ptr<EventListener> listener) override {};

  /*
  void SetStyleLine(StyleLine style) override {};
  StyleLine StyleLine() const override {};
  */

public slots:
  void SendSceneQPainter(QPainter & painter) {};

};