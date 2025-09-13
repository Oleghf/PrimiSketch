#include <QMenuBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>

#include <QtAdapters.h>
#include <PropertiesPanelWidget.h>
#include <ConstructionPanelWidget.h>
#include <SceneWidget.h>
#include <EditorToolBar.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <ScenePaintEvent.h>
#include <ToolChangeEvent.h>
#include <ExportSVGEvent.h>
#include <SceneMouseEvent.h>
#include <UndoEvent.h>
#include <RedoEvent.h>
#include <LoadFileEvent.h>
#include <SaveFileEvent.h>
#include <EventListener.h>
#include <Event.h>
#include <QtPainter.h>
#include <QtView.h>


//------------------------------------------------------------------------------
/**
  Устанавливает меню и горячие клавиши
*/
//---
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


//------------------------------------------------------------------------------
/**
  Устанавливает виджеты сцены, панели создания фигуры, панели свойств, панели инструментов в основное окно приложения
*/
//---
void QtView::SetupWidgets()
{
  QVBoxLayout * mainVertLayout = new QVBoxLayout(m_centralWidget);
  QHBoxLayout * subHorizLayout = new QHBoxLayout();

  m_scene->setMinimumSize(m_centralWidget->size());
  m_scene->setMouseTracking(true);

  subHorizLayout->addWidget(m_scene,9);
  subHorizLayout->addWidget(m_properties,1);
  subHorizLayout->addStretch();

  mainVertLayout->addLayout(subHorizLayout, 9);
  mainVertLayout->addWidget(m_construction, 1);
  mainVertLayout->addStretch();

  addToolBar(m_toolBar);
}


//------------------------------------------------------------------------------
/**
  Отправляет ивент слушателям
*/
//---
void QtView::SendEvent(const Event& event)
{
  for (auto & obs : m_listeners)
  {
    if (obs)
      obs->OnEvent(event);
  }
}


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \details Инициализирует виджеты, вызывает функции установщики, соединяет сигналы
*/
//---
QtView::QtView()
  : QMainWindow(nullptr)
  , m_scene(new SceneWidget())
  , m_properties(new PropertiesPanelWidget())
  , m_construction(new ConstructionPanelWidget())
  , m_centralWidget(new QWidget())
  , m_toolBar(new EditorToolBar(this))
{
  setCentralWidget(m_centralWidget);
  SetupMenu();
  SetupWidgets();

  connect(m_scene, &SceneWidget::CreatedQPainter, this, &QtView::CreateScenePaintEvent);
  connect(m_scene, &SceneWidget::CreatedQMouseEvent, [this](QMouseEvent * ev) { SendEvent(qt_adapters::FromQMouseEvent(ev)); });
  connect(m_open, &QAction::triggered, [this]() { SendEvent(LoadFileEvent()); });
  connect(m_saveAs, &QAction::triggered, [this]() { SendEvent(SaveFileEvent()); });
  connect(m_undo, &QAction::triggered, [this]() { SendEvent(UndoEvent()); });
  connect(m_redo, &QAction::triggered, [this]() { SendEvent(RedoEvent()); });
  connect(m_exportSVG, &QAction::triggered, [this]() { SendEvent(ExportSVGEvent()); });
  connect(m_toolBar, &EditorToolBar::toolChanged, [this](Tool newTool) { SendEvent(ToolChangeEvent(newTool)); });
  connect(m_construction, &ConstructionPanelWidget::AcceptButtonTriggered, [this]() { SendEvent(CompleteDrawingEvent(true)); });
  connect(m_construction, &ConstructionPanelWidget::CancelButtonTriggered, [this]() { SendEvent(CompleteDrawingEvent(false)); });
  connect(m_construction, &ConstructionPanelWidget::AutoBuildCheckBoxChanged, [this](bool isOn) { SendEvent(AutoBuildEvent(isOn)); });
}


//------------------------------------------------------------------------------
/**
  Запрос перерисовки у сцены
*/
//---
void QtView::RequestRedraw()
{
  m_scene->update();
}


//
void QtView::SetActionEnabled(SwitchableEditorAction action, bool isEnabled)
{
    switch (action)
    {
      case SwitchableEditorAction::Accept:
        m_construction->SetActionEnabled(SwitchableConstructionPanelAction::Accept, isEnabled);
        break;
      case SwitchableEditorAction::Cancel:
        m_construction->SetActionEnabled(SwitchableConstructionPanelAction::Cancel, isEnabled);
        break;
      case SwitchableEditorAction::AutoBuild:
        m_construction->SetActionEnabled(SwitchableConstructionPanelAction::AutoBuild, isEnabled);
        break;
      case SwitchableEditorAction::ChangeStyleLine:
        m_properties->SetStyleLineBoxEnabled(isEnabled);
        break;
      case SwitchableEditorAction::Undo:
        m_undo->setEnabled(isEnabled);
        break;
      case SwitchableEditorAction::Redo:
        m_redo->setEnabled(isEnabled);
        break;
      case SwitchableEditorAction::LoadAs:
        m_open->setEnabled(isEnabled);
        break;
      case SwitchableEditorAction::SaveAs:
        m_saveAs->setEnabled(isEnabled);
        break;
    }
}


//
bool QtView::IsActionEnabled(SwitchableEditorAction action) const
{
  switch (action)
  {
    case SwitchableEditorAction::Accept:
      return m_construction->IsActionEnabled(SwitchableConstructionPanelAction::Accept);
    case SwitchableEditorAction::Cancel:
      return m_construction->IsActionEnabled(SwitchableConstructionPanelAction::Cancel);
    case SwitchableEditorAction::AutoBuild:
      return m_construction->IsActionEnabled(SwitchableConstructionPanelAction::AutoBuild);
    case SwitchableEditorAction::ChangeStyleLine:
      return m_properties->IsStyleLineBoxEnabled();
    case SwitchableEditorAction::Undo:
      return m_undo->isEnabled();
    case SwitchableEditorAction::Redo:
      return m_redo->isEnabled();
    case SwitchableEditorAction::LoadAs:
      return m_open->isEnabled();
    case SwitchableEditorAction::SaveAs:
      return m_saveAs->isEnabled();
  }
}


//------------------------------------------------------------------------------
/**
  Установка нового названия процесса в панель свойств
*/
//---
void QtView::SetProcessName(const std::string& nameProcess)
{
  m_properties->SetProcessName(nameProcess);
}


//------------------------------------------------------------------------------
/**
  Получение текущего названия процесса из панели свойств
*/
//---
std::string QtView::GetProccessName() const
{
  return m_properties->GetProcessName();
}


//------------------------------------------------------------------------------
/**
  Открывает диалог сохранения текущего состояния приложения
*/
//---
std::string QtView::OpenSaveFileDialog(const std::string & title, const std::string & initPath, const std::string & filter)
{
  return QFileDialog::getSaveFileName(this, title.c_str(), initPath.c_str(), filter.c_str()).toStdString();
}


//------------------------------------------------------------------------------
/**
  Открывает диалог загрузки состояния приложения
*/
//---
std::string QtView::OpenLoadFileDialog(const std::string & title, const std::string & initPath, const std::string & filter)
{
  return QFileDialog::getOpenFileName(this, title.c_str(), initPath.c_str(), filter.c_str()).toStdString();
}


//------------------------------------------------------------------------------
/**
  Показывает пользователю сообщение выбранного типа
*/
//---
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


//------------------------------------------------------------------------------
/**
  Устанавливает коэфф зума
*/
//---
void QtView::SetZoomFactor(double factor)
{
  m_zoomFactor = std::abs(factor);
}


//------------------------------------------------------------------------------
/**
  Возвращает коэфф зума
*/
//---
double QtView::ZoomFactor() const
{
  return m_zoomFactor;
}


//------------------------------------------------------------------------------
/**
  Добавляет слушателя событий
*/
//---
void QtView::AddEventListener(std::shared_ptr<EventListener> listener)
{
  if (listener)
    m_listeners.push_back(std::move(listener));
}


//------------------------------------------------------------------------------
/**
  Удаляет слушателя событий
*/
//---
void QtView::RemoveEventListener(std::shared_ptr<EventListener> listener)
{
  std::erase(m_listeners, std::move(listener));
}


//------------------------------------------------------------------------------
/**
  Устанавливает стиль отрисовки примитивов
*/
//---
void QtView::SetStyleLine(StyleLine style)
{
  m_properties->SetStyleLine(style);
}


//------------------------------------------------------------------------------
/**
  Возвращает стиль отрисовки примитивов
*/
//---
StyleLine QtView::GetStyleLine() const
{
  return m_properties->GetStyleLine();
}


//------------------------------------------------------------------------------
/**
  Генерирует событие перерисовки сцены
*/
//---
void QtView::CreateScenePaintEvent(QPainter & painter)
{
  QtPainter primView(painter);

  ScenePaintEvent paintEvent(primView);

  SendEvent(paintEvent);
}
