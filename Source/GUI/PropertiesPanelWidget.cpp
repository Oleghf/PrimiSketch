#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QVariant>

#include <PropertiesPanelWidget.h>

//
PropertiesPanelWidget::PropertiesPanelWidget(QWidget * parent)
  : QWidget(parent)
  , m_nameProcessLabel(new QLabel())
  , m_stylesBox(new QComboBox())
{
  QVBoxLayout * verLayout = new QVBoxLayout(this);
  QHBoxLayout * stylesHorizLayout = new QHBoxLayout();

  QLabel * nameStylesBox = new QLabel(tr("Стиль линии"));

  stylesHorizLayout->addWidget(nameStylesBox);
  stylesHorizLayout->addWidget(m_stylesBox);
  stylesHorizLayout->addStretch();

  verLayout->addStretch();
  verLayout->addWidget(m_nameProcessLabel);
  verLayout->addLayout(stylesHorizLayout);
  verLayout->addStretch();

  SetProcessName(tr("Инициализация").toStdString());

  m_stylesBox->addItem(tr("Основная"), static_cast<int>(StyleLine::Main));
  m_stylesBox->addItem(tr("Утолщенная"), static_cast<int>(StyleLine::Thickened));
  m_stylesBox->addItem(tr("Штриховая"), static_cast<int>(StyleLine::Dashed));
  m_stylesBox->addItem(tr("Осевая"), static_cast<int>(StyleLine::Axis));
}


//
void PropertiesPanelWidget::SetProcessName(const std::string& nameProcess)
{
  m_nameProcessLabel->setText(nameProcess.c_str());
}


//
std::string PropertiesPanelWidget::GetProcessName() const
{
  return m_nameProcessLabel->text().toStdString();
}


//
void PropertiesPanelWidget::SetStyleLine(StyleLine newStyle)
{
  int indexStyle = m_stylesBox->findData(static_cast<int>(newStyle));
  
  m_stylesBox->setCurrentIndex(indexStyle);
}


//
StyleLine PropertiesPanelWidget::GetStyleLine() const
{
  int indexStyle = m_stylesBox->currentIndex();

  return static_cast<StyleLine>(m_stylesBox->itemData(indexStyle).toInt());
}


//
void PropertiesPanelWidget::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

  painter.setPen(QPen(Qt::black, 2));
  painter.drawRect(rect());

}
