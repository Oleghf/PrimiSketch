#pragma once


#include <QMainWindow>
#include <QGridLayout>

#include <IView.h>
#include <StyleLine.h>
#include <PropertiesPanelWidget.h>

class SceneWidget;

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

  SceneWidget * m_scene;
  PropertiesPanelWidget * m_properties;

  QWidget * m_centralWidget;
  QGridLayout * m_centralWidgetLayout;

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
  void SetupScene(QGridLayout * layout);
  void SetupProperties(QGridLayout * layout);

public:
  QtView();

  void RequestRedraw() override {};

  void SetActionEnabled(EditorAction action, bool isEnabled) override {};
  bool IsActionEnabled(EditorAction action) override { return true; };

  void SetProcessName(const std::string & string) override {};
  std::string GetProccessName() const override { return ""; };

  std::string OpenSaveFileDialog(const std::string & title, const std::string & initPath) override { return ""; };
  std::string OpenLoadFileDialog(const std::string & title, const std::string & initPath) override { return ""; };
  void ShowMessage(const std::string & title, const std::string & message, MessageType type) override {};

  void SetZoomFactor(double factor) override {};
  double ZoomFactor() const override { return 1.0; };

  void AddEventListener(std::shared_ptr<EventListener> listener) override {};
  void RemoveEventListener(std::shared_ptr<EventListener> listener) override {};

  void SetStyleLine(StyleLine style) override {};
  StyleLine GetStyleLine() const override { return StyleLine::Axis; };

public slots:
  void SendSceneQPainter(QPainter & painter) {};

};