#pragma once

#include <QWidget>


////////////////////////////////////////////////////////////////////////////////
//
/// Виджет сцены
/**
*/
////////////////////////////////////////////////////////////////////////////////
class SceneWidget : public QWidget
{
	Q_OBJECT
public:
  SceneWidget(QWidget * parent = nullptr);

  void mousePressEvent(QMouseEvent * event) override;
  void mouseMoveEvent(QMouseEvent * event) override;
  void mouseReleaseEvent(QMouseEvent * event) override;
  void wheelEvent(QWheelEvent * event) override;
  void keyPressEvent(QKeyEvent * event) override;
  void paintEvent(QPaintEvent * event) override;

signals:
  void CreatedQPainter(QPainter & painter);
  void CreatedQMouseEvent(QMouseEvent * event);
  void CreatedQWheelEvent(QWheelEvent * event);
  void CreatedQKeyEvent(QKeyEvent * event);
};