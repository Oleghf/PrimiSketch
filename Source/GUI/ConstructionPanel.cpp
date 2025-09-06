#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QPainter>

#include <ConstructionPanel.h>


//
ConstructionPanel::ConstructionPanel(QWidget* parent): QWidget(parent)
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

  connect(acceptButton, &QPushButton::click, this, &ConstructionPanel::Accepted);
  connect(cancellButton, &QPushButton::click, this, &ConstructionPanel::Cancelled);
  connect(autoBuildCheck, &QCheckBox::toggled, this, &ConstructionPanel::IsAutoBuilded);
}


//
void ConstructionPanel::paintEvent(QPaintEvent * event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);

  painter.setPen(QPen(Qt::black, 2));
  painter.drawRect(rect());
}
