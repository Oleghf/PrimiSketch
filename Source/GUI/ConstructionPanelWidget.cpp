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

  m_acceptButton = new QPushButton(tr("Применить"));
  m_cancelButton = new QPushButton(tr("Отменить"));
  m_autoBuildCheckBox = new QCheckBox(tr("Автоматическое построение"));

  buttHorizLayout->addWidget(m_acceptButton);
  buttHorizLayout->addWidget(m_cancelButton);

  vertLayout->addLayout(buttHorizLayout);
  vertLayout->addWidget(m_autoBuildCheckBox);
  vertLayout->setAlignment(Qt::AlignCenter);
  vertLayout->addStretch();

  connect(m_acceptButton, &QPushButton::clicked, this, &ConstructionPanelWidget::AcceptButtonTriggered);
  connect(m_cancelButton, &QPushButton::clicked, this, &ConstructionPanelWidget::CancelButtonTriggered);
  connect(m_autoBuildCheckBox, &QCheckBox::toggled, this, &ConstructionPanelWidget::AutoBuildCheckBoxChanged);
  connect(this, &ConstructionPanelWidget::AutoBuildCheckBoxEnabled,
          [this](bool isEnabled)
          {
            if (!isEnabled)
              m_autoBuildCheckBox->setCheckState(Qt::Unchecked);
          });
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


//------------------------------------------------------------------------------
/**
  Включить/Отключить кнопки на панели создания фигуры
*/
//---
void ConstructionPanelWidget::SetActionEnabled(SwitchableConstructionPanelAction action, bool isEnabled)
{
	switch (action)
	{
    case SwitchableConstructionPanelAction::Accept:
      m_acceptButton->setEnabled(isEnabled);
      break;
    case SwitchableConstructionPanelAction::Cancel:
      m_cancelButton->setEnabled(isEnabled);
      break;
    case SwitchableConstructionPanelAction::AutoBuild:
      m_autoBuildCheckBox->setEnabled(isEnabled);
      emit AutoBuildCheckBoxEnabled(isEnabled);
      break;
    }
}


//------------------------------------------------------------------------------
/**
  Узнать о том включены ли кнопки на панели создания фигуры
*/
//---
bool ConstructionPanelWidget::IsActionEnabled(SwitchableConstructionPanelAction action) const
{
  switch (action)
  {
    case SwitchableConstructionPanelAction::Accept:
      return m_acceptButton->isEnabled();
    case SwitchableConstructionPanelAction::Cancel:
      return m_cancelButton->isEnabled();
    case SwitchableConstructionPanelAction::AutoBuild:
      return m_autoBuildCheckBox->isEnabled();
  }
}
