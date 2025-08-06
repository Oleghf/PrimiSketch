#include <QMenuBar>

#include <EditorToolBar.h>
#include <QtView.h>


//
void QtView::setupMenu()
{
  QMenu * fileMenu = menuBar()->addMenu(tr("Файл"));
  QMenu * editingMenu = menuBar()->addMenu(tr("Правка"));
  QMenu * additional = menuBar()->addMenu(tr("Дополнительные функции"));

  fileMenu->addAction(tr("Открыть"));
  fileMenu->addAction(tr("Сохранить как"));

  editingMenu->addAction(tr("Отменить"));
  editingMenu->addAction(tr("Повторить"));

  additional->addAction(tr("Экспорт в SVG"));
}


//
void QtView::setupToolBar()
{
  addToolBar(new EditorToolBar(this));
}


//
QtView::QtView()
	: QMainWindow(nullptr)
{
  setupMenu();
  setupToolBar();
}
