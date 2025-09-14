#pragma once

#include <QWidget>

class QPushButton;
class QCheckBox;

////////////////////////////////////////////////////////////////////////////////
//
/// Выключаемые действия(кнопки) на панели создания фигуры
/**
*/
////////////////////////////////////////////////////////////////////////////////
enum class SwitchableConstructionPanelAction
{
	Accept,
	Cancel,
	AutoBuild
};

////////////////////////////////////////////////////////////////////////////////
//
/// Панель для подтверждения построения фигур
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ConstructionPanelWidget : public QWidget
{
	Q_OBJECT

private:
  QPushButton * m_acceptButton;
  QPushButton * m_cancelButton;
  QCheckBox * m_autoBuildCheckBox;

public:
  ConstructionPanelWidget(QWidget * parent = nullptr);

  void paintEvent(QPaintEvent * event) override;

  void SetActionEnabled(SwitchableConstructionPanelAction action, bool isEnabled);
  bool IsActionEnabled(SwitchableConstructionPanelAction action) const;
signals:
  void AcceptButtonTriggered();
  void CancelButtonTriggered();
  void AutoBuildCheckBoxChanged(bool isTristed);
  void AutoBuildCheckBoxEnabled(bool isEnabled);
};