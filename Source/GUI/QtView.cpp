#include <QMenuBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

#include <SceneWidget.h>
#include <EditorToolBar.h>
#include <QtView.h>


//
void QtView::SetupMenu()
{
  QMenu * fileMenu = menuBar()->addMenu(tr("Файл"));
  QMenu * editingMenu = menuBar()->addMenu(tr("Правка"));
  QMenu * additional = menuBar()->addMenu(tr("Дополнительные функции"));

  m_open = fileMenu->addAction(tr("Открыть"));
  m_saveAs = fileMenu->addAction(tr("Сохранить как"));
  m_undo = editingMenu->addAction(tr("Отменить"));
  m_redo = editingMenu->addAction(tr("Повторить"));
  m_exportSVG = additional->addAction(tr("Экспорт в SVG"));

  m_open->setShortcut(QKeySequence::Open);
  m_saveAs->setShortcut(QKeySequence::SaveAs);
  m_undo->setShortcut(QKeySequence::Undo);
  m_redo->setShortcut(QKeySequence::Redo);

}


//
void QtView::SetupToolBar()
{
  addToolBar(new EditorToolBar(this));
}


//
void QtView::SetupWidgets()
{
  QVBoxLayout * mainVertLayout = new QVBoxLayout(m_centralWidget);
  QHBoxLayout * subHorizLayout = new QHBoxLayout();

  m_scene->setMinimumSize(m_centralWidget->size());

  subHorizLayout->addWidget(m_scene,9);
  subHorizLayout->addWidget(m_properties,1);
  subHorizLayout->addStretch();

  mainVertLayout->addLayout(subHorizLayout, 9);
  mainVertLayout->addWidget(m_construction, 1);
  mainVertLayout->addStretch();
}


//
QtView::QtView()
  : QMainWindow(nullptr)
  , m_scene(new SceneWidget())
  , m_properties(new PropertiesPanelWidget())
  , m_construction(new ConstructionPanel())
  , m_centralWidget(new QWidget())
{
  setCentralWidget(m_centralWidget);
  SetupMenu();
  SetupToolBar();
  SetupWidgets();

  connect(m_scene, &SceneWidget::CreatedQPainter, this, &QtView::SendSceneQPainter);
}


//
void QtView::RequestRedraw()
{
  m_scene->update();
}


//
void QtView::SetProcessName(const std::string& nameProcess)
{
  m_properties->SetProcessName(nameProcess);
}


//
std::string QtView::GetProccessName() const
{
  return m_properties->GetProcessName();
}


//
std::string QtView::OpenSaveFileDialog(const std::string & title, const std::string & initPath)
{
  return QFileDialog::getSaveFileName(this, title.c_str(), initPath.c_str()).toStdString();
}


//
std::string QtView::OpenLoadFileDialog(const std::string& title, const std::string& initPath)
{
  return QFileDialog::getOpenFileName(this, title.c_str(), initPath.c_str()).toStdString();
}


//
void QtView::ShowMessage(const std::string & title, const std::string & message, MessageType type)
{
  switch (type)
  {
    case MessageType::Info:
      QMessageBox::information(this, title.c_str(), message.c_str());
      break;
    case MessageType::Error:
      QMessageBox::critical(this, title.c_str(), message.c_str());
      break;
    case MessageType::Warning:
      QMessageBox::warning(this, title.c_str(), message.c_str());
      break;
  }
}


//
void QtView::SetZoomFactor(double factor)
{
  m_zoomFactor = std::abs(factor);
}


//
double QtView::ZoomFactor() const
{
  return m_zoomFactor;
}


//
void QtView::AddEventListener(std::shared_ptr<EventListener> listener)
{
  m_listeners.push_back(std::move(listener));
}


//
void QtView::RemoveEventListener(std::shared_ptr<EventListener> listener)
{
  std::erase(m_listeners, std::move(listener));
}


//
void QtView::SetStyleLine(StyleLine style)
{
  m_properties->SetStyleLine(style);
}


//
StyleLine QtView::GetStyleLine() const
{
  return m_properties->GetStyleLine();
}


//
void QtView::SendSceneQPainter(QPainter & painter)
{
    // ...
}
