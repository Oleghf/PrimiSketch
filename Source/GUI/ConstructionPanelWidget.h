#pragma once

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
//
/// Панель для подтверждения построения фигур
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ConstructionPanelWidget : public QWidget
{
	Q_OBJECT
public:
  ConstructionPanelWidget(QWidget * parent = nullptr);

  void paintEvent(QPaintEvent * event) override;
signals:
  void IsAccepted(bool is);

  void IsAutoBuilded(bool isOn);
};