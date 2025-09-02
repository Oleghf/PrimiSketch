#include <QPainter>

#include <SceneWidget.h>


//
SceneWidget::SceneWidget(QWidget * parent)
	: QWidget(parent)
{
}


//
void SceneWidget::mousePressEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//
void SceneWidget::mouseMoveEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//
void SceneWidget::mouseReleaseEvent(QMouseEvent * event)
{
  emit CreatedQMouseEvent(event);
}


//
void SceneWidget::paintEvent(QPaintEvent * event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

  painter.setBrush(QBrush(Qt::black));
  painter.drawRect(rect());
  emit CreatedQPainter(painter);
}
