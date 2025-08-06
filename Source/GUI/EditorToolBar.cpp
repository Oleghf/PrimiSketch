#include <QActionGroup>

#include <EditorToolBar.h>


//
EditorToolBar::EditorToolBar(QWidget * parent)
	: QToolBar(parent)
{
  // Создаем кнопки панели инструментов
  QAction * lineSegmentAction = addAction(tr("Отрезок"));
  QAction * brokenLineAction = addAction(tr("Ломанная"));
  QAction * rectangleTwoPointsAction = addAction(tr("Прямоугольник по двум точкам"));
  QAction * rectangleCenterAngleAction = addAction(tr("Прямоугольник по центру и углу"));

  // Делаем все кнопки "вжимаемыми"
  lineSegmentAction->setCheckable(true);
  brokenLineAction->setCheckable(true);
  rectangleTwoPointsAction->setCheckable(true);
  rectangleCenterAngleAction->setCheckable(true);

  // Включаем их в QActionGroup, чтобы установить эксклюзивность кнопок
  // Таким образом только одна кнопка может быть "вжата"
  QActionGroup * actionGroup = new QActionGroup(this);
  actionGroup->addAction(lineSegmentAction);
  actionGroup->addAction(brokenLineAction);
  actionGroup->addAction(rectangleTwoPointsAction);
  actionGroup->addAction(rectangleCenterAngleAction);
  actionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);

  connect(lineSegmentAction, &QAction::toggled,
          [this](bool checked)
          {
            if (checked)
              emit toolChaned(ToolBarAction::LineSegment);
            else
              emit toolChaned(ToolBarAction::None);
          });
  connect(brokenLineAction, &QAction::toggled,
          [this](bool checked)
          {
            if (checked)
              emit toolChaned(ToolBarAction::BrokenLine);
            else
              emit toolChaned(ToolBarAction::None);
          });
  connect(rectangleTwoPointsAction, &QAction::toggled,
          [this](bool checked)
          {
            if (checked)
              emit toolChaned(ToolBarAction::RectangleTwoPoints);
            else
              emit toolChaned(ToolBarAction::None);
          });
  connect(rectangleCenterAngleAction, &QAction::toggled,
          [this](bool checked)
          {
            if (checked)
              emit toolChaned(ToolBarAction::RectangleCenterAngle);
            else
              emit toolChaned(ToolBarAction::None);
          });
}