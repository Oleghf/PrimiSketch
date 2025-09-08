#pragma once


#include <QMainWindow>
#include <QGridLayout>

#include <IView.h>
#include <StyleLine.h>
#include <PropertiesPanelWidget.h>
#include <ConstructionPanelWidget.h>

class Event;
class SceneWidget;
class EditorToolBar;

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

  // Виджеты
  SceneWidget * m_scene;
  PropertiesPanelWidget * m_properties;
  ConstructionPanelWidget * m_construction;
  EditorToolBar * m_toolBar;
  QWidget * m_centralWidget;

  // Действия в редакторе
  QAction * m_open;
  QAction * m_saveAs;
  QAction * m_undo;
  QAction * m_redo;
  QAction * m_exportSVG;

  // Коэффициент масштабирования
  double m_zoomFactor;

 private:
  void SetupMenu();
  void SetupToolBar();
  void SetupWidgets();

  void SendEvent(const Event & event);

public:
  QtView();

  void RequestRedraw() override;

  void SetActionEnabled(EditorAction action, bool isEnabled) override {};
  bool IsActionEnabled(EditorAction action) override { return true; };

  void SetProcessName(const std::string & nameProcess) override;
  std::string GetProccessName() const override;

  std::string OpenSaveFileDialog(const std::string & title, const std::string & initPath) override;
  std::string OpenLoadFileDialog(const std::string & title, const std::string & initPath) override;
  void ShowMessage(const std::string & title, const std::string & message, MessageType type) override;

  void SetZoomFactor(double factor) override;
  double ZoomFactor() const override;

  void AddEventListener(std::shared_ptr<EventListener> listener) override;
  void RemoveEventListener(std::shared_ptr<EventListener> listener) override;

  void SetStyleLine(StyleLine style) override;
  StyleLine GetStyleLine() const override;

public slots:
  void SendSceneQPainter(QPainter & painter);

};