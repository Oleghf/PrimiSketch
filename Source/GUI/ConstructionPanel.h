#pragma once

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
//
/// Панель для подтверждения построения фигур
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ConstructionPanel : public QWidget
{
	Q_OBJECT
public:
  ConstructionPanel(QWidget * parent = nullptr);

  void paintEvent(QPaintEvent * event) override;
signals:
  void Accepted();
  void Cancelled();

  void IsAutoBuilded(bool isOn);
};