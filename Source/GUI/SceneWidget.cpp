#include <QPainter>

#include <SceneWidget.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
SceneWidget::SceneWidget(QWidget * parent)
	: QWidget(parent)
{
}


//------------------------------------------------------------------------------
/**
  Переопределенный метод для обработки нажатия кнопок мыши
*/
//---
void SceneWidget::mousePressEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//------------------------------------------------------------------------------
/**
  Переопределенный метод для обработки движения мыши
*/
//---
void SceneWidget::mouseMoveEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//------------------------------------------------------------------------------
/**
  Переопределенный метод для обработки отпускания кнопок мыши
*/
//---
void SceneWidget::mouseReleaseEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//------------------------------------------------------------------------------
/**
  Переопределенный метод перерисовки виджета
*/
//---
void SceneWidget::paintEvent(QPaintEvent * event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen({Qt::black, 2});
  painter.drawRect(rect());

  emit CreatedQPainter(painter);
}
