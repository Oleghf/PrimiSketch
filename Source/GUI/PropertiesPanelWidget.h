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

  void SetProcessName(const std::string & nameProcess);
  std::string GetProcessName() const;

  void SetStyleLine(StyleLine newStyle);
  StyleLine GetStyleLine() const; 

  void paintEvent(QPaintEvent * event) override;

signals:
  void StyleLineChanged(StyleLine newStyle);
};
