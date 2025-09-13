#include <IView.h>
#include <SceneMouseEvent.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <Rectangle.h>
#include <CreateFigureCommand.h>
#include <ICommand.h>
#include <RenderableModel.h>
#include <CreateRectangleCenterAngleState.h>


//------------------------------------------------------------------------------
/**
  Создает временную(фантомную) фигуру по переданной координате(в виде точки)
*/
//---
void CreateRectangleCenterAngleState::CreateTemporaryFigure(const Point & pos)
{
  m_temporaryRectangle = std::make_shared<Rectangle>(pos, pos);
  m_renderable.SetRenderProperties(m_temporaryRectangle, {0, 0, 0, 155, m_view->GetStyleLine()});
}


//------------------------------------------------------------------------------
/**
  Обновляет конечную точку временной(фантомной) фигуры, если такая была создана
*/
//---
void CreateRectangleCenterAngleState::UpdateEndPosTemporaryFigure(const Point & pos)
{
  Point oppositeAngle{2 * m_firstPos.x - pos.x, 2 * m_firstPos.y - pos.y};
  m_temporaryRectangle->Update(oppositeAngle, pos);
  m_view->RequestRedraw();
}


//------------------------------------------------------------------------------
/**
  Удаляет временную(фантомную) фигуру
*/
//---
void CreateRectangleCenterAngleState::RemoveTemporaryFigure()
{
  m_renderable.Remove(m_temporaryRectangle);
  m_temporaryRectangle = nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnSceneMousePressEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMousePress && mouseEv.Button() == MouseButton::Left)
  {
    if (m_status == Status::AwaitFirstPos)
    {
      m_firstPos = mouseEv.LocalPos();
      m_status = Status::AwaitSecondPos;
      CreateTemporaryFigure(m_firstPos);
    }
    else if (m_status != Status::AwaitConfirm)
    {
      m_secondPos = mouseEv.LocalPos();
      if (m_isAutoBuild)
      {
        m_status = Status::AwaitFirstPos;
        RemoveTemporaryFigure();
        return CreateDrawCommand(m_firstPos, m_secondPos);
      }
      else
        m_status = Status::AwaitConfirm;
    }
  }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
void CreateRectangleCenterAngleState::OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMouseMove)
  {
    if (m_status == Status::AwaitSecondPos && m_status != Status::AwaitConfirm)
      UpdateEndPosTemporaryFigure(mouseEv.LocalPos());
  }
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие изменения галочки "Автоматическое построение"
*/
//---
void CreateRectangleCenterAngleState::OnAutoBuildEvent(const AutoBuildEvent & ev)
{
  m_isAutoBuild = ev.IsAutoBuild();

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, !m_isAutoBuild);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, !m_isAutoBuild);
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  m_status = Status::AwaitFirstPos;

  RemoveTemporaryFigure();
  if (ev.IsDrawAccepted())
    return CreateDrawCommand(m_firstPos, m_secondPos);
  else
    return nullptr;
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание отрезка по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::CreateDrawCommand(const Point & center, const Point & angle)
{
  Point oppositeAngle{2 * center.x - angle.x, 2 * center.y - angle.y};

  std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(oppositeAngle, angle);
  RenderProperties renderableProp{0, 0, 0, 255, m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(rect, renderableProp, m_geometry, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateRectangleCenterAngleState::CreateRectangleCenterAngleState(std::shared_ptr<IView> view, GeometryModel & geometry,
                                                             RenderableModel & renderable)
  : m_view(view)
  , m_geometry(geometry)
  , m_renderable(renderable)
  , m_status(Status::AwaitActivate)
  , m_isAutoBuild(false)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие мыши
*/
//---
std::unique_ptr<ICommand> CreateRectangleCenterAngleState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    case EventType::SceneMouseMove:
    {
      const SceneMouseEvent & mouseEvent = static_cast<const SceneMouseEvent &>(event);
      if (event.Type() == EventType::SceneMousePress)
        return OnSceneMousePressEvent(mouseEvent);
      OnSceneMouseMoveEvent(mouseEvent);
      break;
    }
    case EventType::CompleteDrawing:
    {
      const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);
      return OnCompleteDrawingEvent(completeDrawEvent);
    }
    case EventType::AutoBuild:
    {
      const AutoBuildEvent & autoBuildEv = static_cast<const AutoBuildEvent &>(event);
      OnAutoBuildEvent(autoBuildEv);
      break;
    }
  }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  \brief Перевести состояние в рабочий режим
  \details Устанавливает название процесса, включает необходимые кнопки в редакторе
*/
//---
void CreateRectangleCenterAngleState::Activate()
{
  m_status = Status::AwaitFirstPos;
  m_view->SetProcessName("Фигура: Прямоугольник по центру и углу");

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, true);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, true);
  m_view->SetActionEnabled(SwitchableEditorAction::AutoBuild, true);
  m_view->SetActionEnabled(SwitchableEditorAction::ChangeStyleLine, true);
}


//------------------------------------------------------------------------------
/**
  \brief Отключить состояние
  \details Устанавливает в качестве названия процесса пустую строку
  \warning Не отключает кнопки редактора
*/
//---
void CreateRectangleCenterAngleState::Deactivate()
{
  m_status = Status::AwaitActivate;
  m_view->SetProcessName("");
}
