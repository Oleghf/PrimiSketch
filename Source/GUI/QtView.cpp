#include <QMenuBar>
#include <QHBoxLayout>
#include <QGridLayout>

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
void QtView::SetupScene(QGridLayout* layout)
{
  m_scene->setFixedSize(m_centralWidget->size());

  layout->addWidget(m_scene, 0,0, Qt::AlignTop);
}


//
void QtView::SetupProperties(QGridLayout * layout)
{
  m_properties->setFixedHeight(m_scene->height());
  m_properties->setFixedWidth(m_scene->width() / 4);

  layout->addWidget(m_properties, 0, 1);
}


//
QtView::QtView()
  : QMainWindow(nullptr)
  , m_scene(new SceneWidget())
  , m_properties(new PropertiesPanelWidget())
  , m_centralWidget(new QWidget())
  , m_centralWidgetLayout(new QGridLayout(m_centralWidget))
{
  setCentralWidget(m_centralWidget);
  SetupMenu();
  SetupToolBar();
  SetupScene(m_centralWidgetLayout);
  SetupProperties(m_centralWidgetLayout);
}
