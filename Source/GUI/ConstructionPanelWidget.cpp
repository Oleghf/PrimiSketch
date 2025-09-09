#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QPainter>

#include <ConstructionPanelWidget.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \details Расставляет кнопки и соединяет сигналы
*/
//---
ConstructionPanelWidget::ConstructionPanelWidget(QWidget* parent): QWidget(parent)
{
  QVBoxLayout * vertLayout = new QVBoxLayout(this);
  QHBoxLayout * buttHorizLayout = new QHBoxLayout();

  QPushButton * acceptButton = new QPushButton(tr("Применить"));
  QPushButton * cancellButton = new QPushButton(tr("Отменить"));
  QCheckBox * autoBuildCheck = new QCheckBox(tr("Автоматическое построение"));

  buttHorizLayout->addWidget(acceptButton);
  buttHorizLayout->addWidget(cancellButton);

  vertLayout->addLayout(buttHorizLayout);
  vertLayout->addWidget(autoBuildCheck);
  vertLayout->setAlignment(Qt::AlignCenter);
  vertLayout->addStretch();

  connect(acceptButton, &QPushButton::clicked, this, [this] () {emit IsAccepted(true);});
  connect(cancellButton, &QPushButton::clicked, this, [this]() {emit IsAccepted(false); });
  connect(autoBuildCheck, &QCheckBox::toggled, this, &ConstructionPanelWidget::IsAutoBuilded);
}


//------------------------------------------------------------------------------
/**
  Переопределенный метод отрисовки виджета
*/
//---
void ConstructionPanelWidget::paintEvent(QPaintEvent * event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

  painter.setPen(QPen(Qt::black, 2));
  painter.drawRect(rect());
}
