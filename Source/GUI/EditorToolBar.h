#pragma once

#include <QToolBar>

#include <Tool.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Панель инструментов редактора
/**
*/
////////////////////////////////////////////////////////////////////////////////
class EditorToolBar : public QToolBar
{
	Q_OBJECT
public:
  EditorToolBar(QWidget * parent = nullptr);

signals:
  void toolChanged(Tool newAction);
};