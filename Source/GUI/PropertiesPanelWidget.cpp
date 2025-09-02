#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

#include <PropertiesPanelWidget.h>

//
PropertiesPanelWidget::PropertiesPanelWidget(QWidget * parent)
  : QWidget(parent)
  , m_nameProcessLabel(new QLabel())
  , m_stylesBox(new QComboBox())
{
  QVBoxLayout * verLayout = new QVBoxLayout(this);

  verLayout->addStretch();
  verLayout->addWidget(m_nameProcessLabel);
  verLayout->addWidget(m_stylesBox);
  verLayout->addStretch();

  setNameProcess("Инициализация");

  m_stylesBox->addItem("Основная");
  m_stylesBox->addItem("Утолщенная");
  m_stylesBox->addItem("Штриховка");
  m_stylesBox->addItem("Осевая");
}


//
void PropertiesPanelWidget::setNameProcess(const std::string& nameProcess)
{
  m_nameProcessLabel->setText(nameProcess.c_str());
}


//
std::string PropertiesPanelWidget::nameProcess() const
{
  return m_nameProcessLabel->text().toStdString();
}


//
void PropertiesPanelWidget::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

}
