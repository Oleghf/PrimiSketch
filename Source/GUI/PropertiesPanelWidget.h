#pragma once

#include <QWidget>

#include <StyleLine.h>

class QLabel;
class QComboBox;

////////////////////////////////////////////////////////////////////////////////
//
/// Виджет характеристик строющегося объекта
/**
*/
////////////////////////////////////////////////////////////////////////////////
class PropertiesPanelWidget : public QWidget
{
	Q_OBJECT

private:
  QLabel * m_nameProcessLabel;
  QComboBox * m_stylesBox;

public:
  PropertiesPanelWidget(QWidget * parent = nullptr);

  void setNameProcess(const std::string & nameProcess);
  std::string nameProcess() const;

  void setStyleLine(StyleLine newStyle) {};
  StyleLine styleLine() const { StyleLine::Axis; }; 

  void paintEvent(QPaintEvent * event) override;

signals:
  void StyleLineChanged(StyleLine newStyle);
};
