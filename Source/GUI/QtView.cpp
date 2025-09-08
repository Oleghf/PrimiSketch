#include <QMenuBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

#include <ExportSVGEvent.h>
#include <UndoEvent.h>
#include <RedoEvent.h>
#include <LoadFileEvent.h>
#include <SaveFileEvent.h>
#include <EventListener.h>
#include <Event.h>
#include <QtPainter.h>
#include <ScenePaintEvent.h>
#include <SceneWidget.h>
#include <EditorToolBar.h>
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
  Устанавливает меню инструментов
*/
//---
void QtView::SetupToolBar()
{
  addToolBar(new EditorToolBar(this));
}


//------------------------------------------------------------------------------
/**
  Устанавливает виджеты сцены, панели создания фигуры, панели свойств в основное окно приложения
*/
//---
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


//------------------------------------------------------------------------------
/**
  Отправляет ивент слушателям
*/
//---
void QtView::SendEvent(const Event& event)
{
  for (auto obs : m_listeners)
    obs->OnEvent(event);
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
{
  setCentralWidget(m_centralWidget);
  SetupMenu();
  SetupToolBar();
  SetupWidgets();

  connect(m_scene, &SceneWidget::CreatedQPainter, this, &QtView::SendSceneQPainter);
  connect(m_open, &QAction::trigger, this, [this]() { SendEvent(LoadFileEvent()); });
  connect(m_saveAs, &QAction::trigger, this, [this]() { SendEvent(SaveFileEvent()); });
  connect(m_undo, &QAction::trigger, this, [this]() { SendEvent(UndoEvent()); });
  connect(m_redo, &QAction::trigger, this, [this]() { SendEvent(RedoEvent()); });
  connect(m_exportSVG, &QAction::trigger, this, [this]() { SendEvent(ExportSVGEvent()); });
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
std::string QtView::OpenSaveFileDialog(const std::string & title, const std::string & initPath)
{
  return QFileDialog::getSaveFileName(this, title.c_str(), initPath.c_str()).toStdString();
}


//------------------------------------------------------------------------------
/**
  Открывает диалог загрузки состояния приложения
*/
//---
std::string QtView::OpenLoadFileDialog(const std::string& title, const std::string& initPath)
{
  return QFileDialog::getOpenFileName(this, title.c_str(), initPath.c_str()).toStdString();
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
void QtView::SendSceneQPainter(QPainter & painter)
{
  QtPainter primView(painter);

  ScenePaintEvent paintEvent(primView);

  SendEvent(paintEvent);
}
